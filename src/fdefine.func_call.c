//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.em_js.h"
//silver_chain_scope_end
EMSCRIPTEN_KEEPALIVE long c2wasm_call_c_function_with_internal_args(c2wasm_js_var internal_args,void *callback){
    long (*converted_callback)(long internal_args) = (long (*)(long))callback;
    return converted_callback(internal_args);
}

EMSCRIPTEN_KEEPALIVE long c2wasm_call_c_function(void *callback){
    long (*converted_callback)() = (long (*)())callback;
    return converted_callback();
}