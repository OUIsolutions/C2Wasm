//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.macro.h"
//silver_chain_scope_end
EM_JS(long ,c2wasm_get_array_long_by_index,(long stack_index, int index), {
    let array = window.c2wasm_stack[stack_index];
    return array[index];
});

EM_JS(double ,c2wasm_get_array_double_by_index,(long stack_index, int index), {
    let array = window.c2wasm_stack[stack_index];
    return array[index];
});

EM_JS(long ,c2wasm_get_array_any_by_index,(long stack_index, int index), {
    let array = window.c2wasm_stack[stack_index];
    let created_index = window.c2wasm_stack.length;
    window.c2wasm_stack.push(array[created_index]);
    return created_index;
});

EM_JS(int,c2wasm_is_array_index_true,(long stack_index, int index),{
    let array = window.c2wasm_stack[stack_index];
    return array[index] == true;
});

EM_JS(int,c2wasm_is_array_index_undefined,(long stack_index, int index),{
    let array = window.c2wasm_stack[stack_index];
    return array[index] == undefined;
});

EM_JS(int,c2wasm_is_array_index_null,(long stack_index, int index),{
    let array = window.c2wasm_stack[stack_index];
    return array[index] == null;
});
