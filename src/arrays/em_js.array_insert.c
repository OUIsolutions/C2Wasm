//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.macro.h"
//silver_chain_scope_end
EM_JS(void, c2wasm_insert_array_long_by_index, (long stack_index, int index, long value), {
    let array = window.c2wasm_stack[stack_index];
    array.splice(index, 0, value);
});

EM_JS(void, c2wasm_insert_array_double_by_index, (long stack_index, int index, double value), {
    let array = window.c2wasm_stack[stack_index];
    array.splice(index, 0, value);
});

EM_JS(void, c2wasm_insert_array_string_by_index, (long stack_index, int index, const char *value), {
    let array = window.c2wasm_stack[stack_index];
    array.splice(index, 0, window.c2wasm_get_string(value));
});

EM_JS(void, c2wasm_insert_array_any_by_index, (long stack_index, int index, int stack_index_value), {
    let array = window.c2wasm_stack[stack_index];
    array.splice(index, 0, window.c2wasm_stack[stack_index_value]);
});

EM_JS(void, c2wasm_insert_array_bool_by_index, (long stack_index, int index, int value), {
    let array = window.c2wasm_stack[stack_index];
    array.splice(index, 0, value ? true : false);
});
