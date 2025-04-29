//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.macro.h"
//silver_chain_scope_end


EM_JS(void,c2wasm_soft_free,(long stack_index),{
    if(window.c2wasm_stack.length <= stack_index){
        return;
    }
    window.c2wasm_stack[stack_index] = undefined;
});

EM_JS(void,c2wasm_hard_free,(long stack_index),{
    if(window.c2wasm_stack.length <= stack_index){
        return;
    }
    delete window.c2wasm_stack[stack_index];
});
