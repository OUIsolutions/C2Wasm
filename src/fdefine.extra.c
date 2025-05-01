//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.em_js.h"
//silver_chain_scope_end





EMSCRIPTEN_KEEPALIVE char c2wasm_get_char(const char *str,int index) {
    return str[index];
}


EMSCRIPTEN_KEEPALIVE void* c2wasm_memcpy(char *dest, const char *src, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
    return dest;
}