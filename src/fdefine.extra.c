//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.em_js.h"
//silver_chain_scope_end


long private_emcc_strlen(const char *str) {
    long len = 0;
    while(str[len] != '\0') {
        len++;
    }
    return len;
}


EMSCRIPTEN_KEEPALIVE char c2wasm_get_char(const char *str,int index) {
    return str[index];
}
EMSCRIPTEN_KEEPALIVE void c2wasm_set_char(char *str,int index,char value) {
    str[index] = value;
}
EMSCRIPTEN_KEEPALIVE int c2wasm_get_str_size(const char *str) {
    return private_emcc_strlen(str);
}
#include <stdio.h>
EMSCRIPTEN_KEEPALIVE void c2wasm_clear_all_except(const int *keep, int size) {
    long size_stack = c2wasm_get_stack_size();
    for(long i = 9; i < size_stack; i++) {
        int should_keep = 0;
        for(int j = 0; j < size; j++) {
            if(keep[j] == i) {
                should_keep = 1;
                printf("keeping %ld\n", i);
                break;
            }
        }
        if(!should_keep) {
            c2wasm_free(i);
        }
    }
}

EM_JS(void ,c2wasm_show_var_on_console,(long stack_index), {
    let element = window.c2wasm_stack[stack_index];
    console.log(element);
});
