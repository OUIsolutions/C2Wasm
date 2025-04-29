EM_JS(long,c2wasm_create_long,(long value),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push(value);
    return index;
});

EM_JS(long,c2wasm_create_double,(double value),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push(value);
    return index;
});

EM_JS(long,c2wasm_create_object,(void),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push({});
    return index;
});

EM_JS(long,c2wasm_create_array,(void),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push([]);
    return index;
});

EM_JS(long,c2wasm_create_string,(const char *value),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push(value);
    return index;
});