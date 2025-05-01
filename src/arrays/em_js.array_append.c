//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.macro.h"
//silver_chain_scope_end
/*
  ______                                                                  __ 
 /      \                                                                /  |
/$$$$$$  |         ______    ______    ______    ______   _______    ____$$ |
$$ |__$$ | ______ /      \  /      \  /      \  /      \ /       \  /    $$ |
$$    $$ |/      |$$$$$$  |/$$$$$$  |/$$$$$$  |/$$$$$$  |$$$$$$$  |/$$$$$$$ |
$$$$$$$$ |$$$$$$/ /    $$ |$$ |  $$ |$$ |  $$ |$$    $$ |$$ |  $$ |$$ |  $$ |
$$ |  $$ |       /$$$$$$$ |$$ |__$$ |$$ |__$$ |$$$$$$$$/ $$ |  $$ |$$ \__$$ |
$$ |  $$ |       $$    $$ |$$    $$/ $$    $$/ $$       |$$ |  $$ |$$    $$ |
$$/   $$/         $$$$$$$/ $$$$$$$/  $$$$$$$/   $$$$$$$/ $$/   $$/  $$$$$$$/ 
                           $$ |      $$ |                                    
                           $$ |      $$ |                                    
                           $$/       $$/                                     
*/
EM_JS(void, c2wasm_append_array_long, (c2wasm_js_var stack_index, long value), {
    let array = window.c2wasm_stack[stack_index];
    array.push(value);
});

EM_JS(void, c2wasm_append_array_double, (c2wasm_js_var stack_index, double value), {
    let array = window.c2wasm_stack[stack_index];
    array.push(value);
});

EM_JS(void, c2wasm_append_array_string, (c2wasm_js_var stack_index, const char *value), {
    let array = window.c2wasm_stack[stack_index];
    array.push(window.c2wasm_get_string(value));
});

EM_JS(void, c2wasm_append_array_any, (c2wasm_js_var stack_index, c2wasm_js_var stack_index_value), {
    let array = window.c2wasm_stack[stack_index];
    array.push(window.c2wasm_stack[stack_index_value]);
});

EM_JS(void, c2wasm_append_array_bool, (c2wasm_js_var stack_index, int value), {
    let array = window.c2wasm_stack[stack_index];
    array.push(value ? true : false);
});