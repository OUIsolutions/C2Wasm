let c2wasm = function(){

    let main_module = {}
    main_module.createEnv = function(stack,lib) {

        let env_obj = {}
        

        return env_obj;
    } 
    main_module.loadBytes = async function(wasmBytes, callback) {

        let created_obj = {};
        created_obj.lib = {};
        created_obj.stack = [];
        created_obj.env =  main_module.createEnv(created_obj.stack,created_obj.lib);
        created_obj.wasmModule = await WebAssembly.instantiate(wasmBytes, created_obj.env);
        return created_obj;
    }
    main_module.loadModule = async function(module, callback) {
        let wasmBytes = await fetch(module).then(res => res.arrayBuffer());
        return main_module.loadBytes(wasmBytes, callback);
    }
    return main_module;

}()
