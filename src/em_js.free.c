//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.macro.h"
//silver_chain_scope_end
EM_JS(void,c2wasm_free,(long stack_index),{
    if(window.c2wasm_stack.length <= stack_index){
        return;
    }

    delete window.c2wasm_stack[stack_index];
});
EM_JS(long,c2wasm_get_stack_size,(void),{
    return window.c2wasm_stack.length;
});