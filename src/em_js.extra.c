//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.macro.h"
//silver_chain_scope_end

EM_JS(long ,c2wasm_get_string_len, (c2wasm_js_var string_index), {
    return window.c2wasm_stack[string_index].length;
});

EM_JS(void *,c2wasm_memcpy_string,(c2wasm_js_var stack_index,int start_string, char *dest, int size), {
    let value = window.c2wasm_stack[stack_index];
    for(let i = 0; i < size; i++){
      
        let current_char = value.charCodeAt(i+start_string);
        if(isNaN(current_char)){
            break;
        }
        wasmExports.c2wasm_set_char(dest,i,current_char);
    }
    return dest;
});
