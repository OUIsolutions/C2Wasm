EMSCRIPTEN_KEEPALIVE long c2wasm_call_c_function_with_internal_args(long internal_args,void *callback){
    long (*converted_callback)(long internal_args) = (long (*)(long))callback;
    return converted_callback(internal_args);
}

EMSCRIPTEN_KEEPALIVE long c2wasm_call_c_function(void *callback){
    long (*converted_callback)() = (long (*)())callback;
    return converted_callback();
}