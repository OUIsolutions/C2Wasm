let c2wasm = function(){
    let envcallbacks = {}
    let cfunctions = {}
    let main_obj = {
        envcallbacks: envcallbacks,
        cfunctions: cfunctions
    } 

//srcjs/teste.js

main_obj.test = function() {
    console.log("test");
    return "test";
}
return main_obj;}()
