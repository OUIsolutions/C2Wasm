//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.em_js.h"
//silver_chain_scope_end





EMSCRIPTEN_KEEPALIVE char c2wasm_get_char(const char *str,int index) {
    return str[index];
}


EM_JS(void,c2wasm_free,(long stack_index),{
    if(window.c2wasm_stack.length <= stack_index){
        return;
    }
    if(window.c2wasm_local_stack){
        //itremove the stack index from old_created obj
        let index_of_stack = window.c2wasm_local_stack.indexOf(stack_index);
        window.c2wasm_local_stack.splice(index_of_stack, 1);
    }
    delete window.c2wasm_stack[stack_index];
});
