//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.macro.h"
//silver_chain_scope_end

/*
  ______                                 __     
 /      \                               /  |    
/$$$$$$  |          _______   ______   _$$ |_   
$$ |__$$ | ______  /       | /      \ / $$   |  
$$    $$ |/      |/$$$$$$$/ /$$$$$$  |$$$$$$/   
$$$$$$$$ |$$$$$$/ $$      \ $$    $$ |  $$ | __ 
$$ |  $$ |         $$$$$$  |$$$$$$$$/   $$ |/  |
$$ |  $$ |        /     $$/ $$       |  $$  $$/ 
$$/   $$/         $$$$$$$/   $$$$$$$/    $$$$/  
*/
EM_JS(void ,c2wasm_set_array_long_by_index,(c2wasm_js_var stack_index, int index, long value), {
    let array = window.c2wasm_stack[stack_index];
    array[index] = value;
});

EM_JS(void ,c2wasm_set_array_double_by_index,(c2wasm_js_var stack_index, int index, double value), {
    let array = window.c2wasm_stack[stack_index];
    array[index] = value;
});

EM_JS(void ,c2wasm_set_array_string_by_index,(c2wasm_js_var stack_index, int index, const char *value), {
    let array = window.c2wasm_stack[stack_index];
    array[index] = window.c2wasm_get_string(value);
});

EM_JS(void ,c2wasm_set_array_any_by_index,( c2wasm_js_var stack_index, int index, int stack_index_value),{
    let array = window.c2wasm_stack[stack_index];
    array[index] = window.c2wasm_stack[stack_index_value];
})

EM_JS(void ,c2wasm_set_array_bool_by_index,(    c2wasm_js_var stack_index, int index, int value), {
    let array = window.c2wasm_stack[stack_index];
    if (value == 0){
        array[index] = false;
    }
    if (value > 0){
        array[index] = true;
    }
});

EM_JS(void ,c2wasm_set_array_null_by_index,(c2wasm_js_var stack_index, int index), {
    let array = window.c2wasm_stack[stack_index];
    array[index] = null;
});

EM_JS(void ,c2wasm_set_array_undefined_by_index,(c2wasm_js_var stack_index, int index), {
    let array = window.c2wasm_stack[stack_index];
    array[index] = undefined;
});