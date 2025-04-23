let c2wasm = function(){

    let extract_str = function(cfuncs,str){
        let buffer = [];
        let size = cfuncs.cfuncs.c2wasm_get_string_size(str);
        for (let i = 0; i < size; i++) {
            let char = cfuncs.cfuncs.c2wasm_get_char_from_string(str,i);
            buffer.push(char);
        }
        let result = String.fromCharCode.apply(null, buffer);
        return result;
    }


    let main_module = {}
    main_module.createEnv = function(stack,cfuncs) {
        let env_obj = {}
        
        env_obj.setIntProp = function(stack_index,name_cstr, value) {
           let name = extract_str(cfuncs,name_cstr);
           console.log("setIntprop",name,value);
           let obj = stack[stack_index];
           obj[name] = value;
        }

        return env_obj;
    } 
    main_module.loadBytes = async function(wasmBytes, startCCallback) {

        let created_obj = {};
        let cfuncs = {};

        created_obj.lib = {};

        
        created_obj.stack = [created_obj.lib];
        created_obj.importObject = {
            module: {},

            env: {
                memory: new WebAssembly.Memory({ initial: 256 }),
                table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
            },
        };
        created_obj.wasmModule = await WebAssembly.instantiate(wasmBytes, created_obj.importObject);
        cfuncs.cfuncs = created_obj.wasmModule.instance.exports;
        cfuncs.cfuncs[startCCallback](0);
        return created_obj;
    }
    main_module.loadModule = async function(module, callback) {
        let wasmBytes = await fetch(module).then(res => res.arrayBuffer());
        return await main_module.loadBytes(wasmBytes, callback);
    }
    return main_module;

}()
