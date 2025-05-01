//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.macro.h"
//silver_chain_scope_end


/*
  ______                                 __     
 /      \                               /  |    
/$$$$$$  |          ______    ______   _$$ |_   
$$ |__$$ | ______  /      \  /      \ / $$   |  
$$    $$ |/      |/$$$$$$  |/$$$$$$  |$$$$$$/   
$$$$$$$$ |$$$$$$/ $$ |  $$ |$$    $$ |  $$ | __ 
$$ |  $$ |        $$ \__$$ |$$$$$$$$/   $$ |/  |
$$ |  $$ |        $$    $$ |$$       |  $$  $$/ 
$$/   $$/          $$$$$$$ | $$$$$$$/    $$$$/  
                  /  \__$$ |                    
                  $$    $$/                     
                   $$$$$$/                      
*/
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

    let value = array[index];
    if(value == false){
        return  window.c2wasm_false;
    }
    if(value == true){
        return window.c2wasm_true;
    }
    if(value == null){
        return window.c2wasm_null;
    }
    if(value == undefined){
        return window.c2wasm_undefined;
    }
    let created_index = window.c2wasm_get_stack_point();
    window.c2wasm_stack[created_index] = value;
    return created_index;
});

