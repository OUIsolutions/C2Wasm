
EMSCRIPTEN_KEEPALIVE void c2wasm_set_object_prop_function_with_internal_args(long stack_index, const char *prop_name, long internal_args, long (*callback)(long internal_args)){
    private_c2wasm_set_object_prop_function_with_internal_args_raw(stack_index,prop_name,internal_args,callback);
}

EMSCRIPTEN_KEEPALIVE void c2wasm_set_object_prop_function(long stack_index, const char *prop_name, long (*callback)()){
    private_c2wasm_set_object_prop_function_raw(stack_index,prop_name,callback);
}