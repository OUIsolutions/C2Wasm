//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.em_js.h"
//silver_chain_scope_end





EMSCRIPTEN_KEEPALIVE char c2wasm_get_char(const char *str,int index) {
    return str[index];
}
EMSCRIPTEN_KEEPALIVE void c2wasm_set_char(char *str,int index,char value) {
    str[index] = value;
}


EM_JS(void ,c2wasm_show_var_on_console,(long stack_index), {
    let element = window.c2wasm_stack[stack_index];
    console.log(element);
});
