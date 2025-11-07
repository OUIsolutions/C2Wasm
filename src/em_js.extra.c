//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.macro.h"
//silver_chain_scope_end

EM_JS(long ,c2wasm_get_string_len, (c2wasm_js_var string_index), {
    let value = window.c2wasm_stack[string_index];
    let encoder = new TextEncoder();
    let utf8Array = encoder.encode(value);
    return utf8Array.length;
});

EM_JS(void *,c2wasm_memcpy_string,(c2wasm_js_var stack_index,int start_string, char *dest, int size), {
    let value = window.c2wasm_stack[stack_index];
    let encoder = new TextEncoder();
    let utf8Array = encoder.encode(value);
    
    for(let i = 0; i <= size; i++){
        if(i + start_string >= utf8Array.length){
            break;
        }
        wasmExports.c2wasm_set_char(dest, i, utf8Array[i + start_string]);
    }
    return dest;
});
