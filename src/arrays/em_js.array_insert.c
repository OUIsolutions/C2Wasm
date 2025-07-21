//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.macro.h"
//silver_chain_scope_end

/*
  ______           __                                            __     
 /      \         /  |                                          /  |    
/$$$$$$  |        $$/  _______    _______   ______    ______   _$$ |_   
$$ |__$$ | ______ /  |/       \  /       | /      \  /      \ / $$   |  
$$    $$ |/      |$$ |$$$$$$$  |/$$$$$$$/ /$$$$$$  |/$$$$$$  |$$$$$$/   
$$$$$$$$ |$$$$$$/ $$ |$$ |  $$ |$$      \ $$    $$ |$$ |  $$/   $$ | __ 
$$ |  $$ |        $$ |$$ |  $$ | $$$$$$  |$$$$$$$$/ $$ |        $$ |/  |
$$ |  $$ |        $$ |$$ |  $$ |/     $$/ $$       |$$ |        $$  $$/ 
$$/   $$/         $$/ $$/   $$/ $$$$$$$/   $$$$$$$/ $$/          $$$$/  
*/
EM_JS(void, c2wasm_insert_array_long_by_index, (c2wasm_js_var stack_index, int index, long value), {
    let array = window.c2wasm_stack[stack_index];
    array.splice(index, 0, value);
});

EM_JS(void, c2wasm_insert_array_double_by_index, (c2wasm_js_var stack_index, int index, double value), {
    let array = window.c2wasm_stack[stack_index];
    array.splice(index, 0, value);
});

EM_JS(void, c2wasm_insert_array_string_by_index, (c2wasm_js_var stack_index, int index, const char *value), {
    let array = window.c2wasm_stack[stack_index];
    array.splice(index, 0, window.c2wasm_get_string(value));
});

EM_JS(void, c2wasm_insert_array_any_by_index, (c2wasm_js_var stack_index, int index, c2wasm_js_var stack_index_value), {
    let array = window.c2wasm_stack[stack_index];
    array.splice(index, 0, window.c2wasm_stack[stack_index_value]);
});

EM_JS(void, c2wasm_insert_array_bool_by_index, (c2wasm_js_var stack_index, int index, int value), {
    let array = window.c2wasm_stack[stack_index];
    array.splice(index, 0, value ? true : false);
});
