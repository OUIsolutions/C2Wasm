let c2wasm = function(){
    let envcallbacks = {}
    let cfunctions = {}
    let exports = null;
    envcallbacks.set_function = function(name, func) {
       console.log("set_function", name, func);
    }





    let main_obj = {
        envcallbacks: envcallbacks,
        cfunctions: cfunctions
    } 
    return main_obj;

}()
