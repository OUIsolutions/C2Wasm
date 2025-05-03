//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.macro.h"
//silver_chain_scope_end

EM_JS(long ,c2wasm_get_string_size, (c2wasm_js_var string_index), {
    return window.c2wasm_stack[string_index].length;
});
