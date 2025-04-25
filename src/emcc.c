#include  "emcc_exports.h"
#include "c2WasmVar.h"


C2wasmVar c2wasm_window = {0, 0};



EM_JS(void ,c2wasm_start, (void), {
 
   if(window['c2wasm_stack'] == undefined){
      window['c2wasm_stack'] = [[window]];
   }
});


EM_JS(void ,c2wasm_set_int_prop,(C2wasmVar *js_var,const char *prop_name, int value), {
    let stack_index = wasmExports.C2wasmVar_get_stack_index(js_var);
    let internal_stack_index = wasmExports.C2wasmVar_get_internal_stack_index(js_var);
    let object = window['c2wasm_stack'][stack_index][internal_stack_index];
    let prop_name_formatted = UTF8ToString(prop_name);
    object[prop_name_formatted] = value;
});