let c2wasm = function() {

    let extract_str = function(cfuncs, str) {
        let buffer = [];
        let size = cfuncs.cfuncs.c2wasm_get_string_size(str);
        for (let i = 0; i < size; i++) {
            let char = cfuncs.cfuncs.c2wasm_get_char_from_string(str, i);
            buffer.push(char);
        }
        let result = String.fromCharCode.apply(null, buffer);
        return result;
    };

    let main_module = {};

    main_module.createEnv = function(stack, cfuncs, memory) {
        let env_obj = {};
        env_obj.memory =    new WebAssembly.Memory({ initial: 256 });


        env_obj.strlen = function(str) {
            let size = 0;
            while (str[size] !== 0) {
                size++;
            }
            return size;
        };

        env_obj.c2wasm_set_int_prop = function(stack_index, name_cstr, value) {
            console.log("setIntprop", stack_index, name_cstr, value);
            return;
            let name = extract_str(cfuncs, name_cstr);
            let obj = stack[stack_index];
            obj[name] = value;
        };
        env_obj.__memory_base = 0;
        env_obj.__table_base = 0;
        env_obj.__stack_pointer = new WebAssembly.Global({ value: "i32", mutable: true }, 0);
        env_obj.table = new WebAssembly.Table({ initial: 0, element: 'anyfunc' });
        return env_obj;
    };

    main_module.loadBytes = async function(wasmBytes, startCCallback) {
        let created_obj = {};
        let cfuncs = {};

        created_obj.lib = {};
        created_obj.stack = [created_obj.lib];

        
        created_obj.importObject = {
            module: {},
            env: main_module.createEnv(created_obj.stack, cfuncs)
        };

     
        created_obj.wasmModule = await WebAssembly.instantiate(wasmBytes, created_obj.importObject);
        cfuncs.cfuncs = created_obj.wasmModule.instance.exports;
        cfuncs.cfuncs[startCCallback]();

        return created_obj;
    };

    main_module.loadModule = async function(module, callback) {
        let wasmBytes = await fetch(module).then(res => res.arrayBuffer());
        return await main_module.loadBytes(wasmBytes, callback);
    };

    return main_module;

}();
