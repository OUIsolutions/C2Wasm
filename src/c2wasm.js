let c2wasm = function(){

    let main_module = {}
    main_module.createEnv = function(stack,cfuncs) {
        let env_obj = {}
        

        return env_obj;
    } 
    main_module.loadBytes = async function(wasmBytes, startCCallback) {

        let created_obj = {};
        let cfuncs = {};

        created_obj.lib = {};
        created_obj.stack = [created_obj.lib];
        created_obj.importObject = {
            env:main_module.createEnv(created_obj.stack,cfuncs)
        };
        created_obj.wasmModule = await WebAssembly.instantiate(wasmBytes, created_obj.importObject);
        cfuncs.cfuncs = created_obj.wasmModule.instance.exports;
        cfuncs.cfuncs[startCCallback](0);
        return created_obj;
    }
    main_module.loadModule = async function(module, callback) {
        let wasmBytes = await fetch(module).then(res => res.arrayBuffer());
        return main_module.loadBytes(wasmBytes, callback);
    }
    return main_module;

}()
