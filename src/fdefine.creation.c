//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.em_js.h"
//silver_chain_scope_end


c2wasm_js_var   c2wasm_create_function_with_internal_args(c2wasm_js_var internal_args,  c2wasm_js_var (*callback)(c2wasm_js_var internal_args)) {
    return c2wasm_create_function_with_internal_argsraw(internal_args, callback);
}

c2wasm_js_var   c2wasm_create_function(c2wasm_js_var (*callback)()) {
    return c2wasm_create_function_raw(callback);
}