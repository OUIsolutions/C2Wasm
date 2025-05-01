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
$$ |  $$ | ______  /       | /      \ / $$   |  
$$ |  $$ |/      |/$$$$$$$/ /$$$$$$  |$$$$$$/   
$$ |  $$ |$$$$$$/ $$      \ $$    $$ |  $$ | __ 
$$ \__$$ |         $$$$$$  |$$$$$$$$/   $$ |/  |
$$    $$/         /     $$/ $$       |  $$  $$/ 
 $$$$$$/          $$$$$$$/   $$$$$$$/    $$$$/  
                                                
                                            
*/
EM_JS(void ,c2wasm_set_object_prop_long,(long stack_index, const char *prop_name, long value), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    object[prop_name_formatted] = value;
});

EM_JS(void ,c2wasm_set_object_prop_double,(long stack_index, const char *prop_name, float value), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    object[prop_name_formatted] = value;
});

EM_JS(void ,c2wasm_set_object_prop_string,(long stack_index, const char *prop_name, const char *value), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let value_formatted = window.c2wasm_get_string(value);
    object[prop_name_formatted] = value_formatted;
});

EM_JS(void ,c2wasm_set_object_prop_bool,(c2wasm_js_var stack_index, const char *prop_name, int value), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    if (value == 0){
        object[prop_name_formatted] = false;
    }
    if (value > 0){
        object[prop_name_formatted] = true;
    }
});

EM_JS(void ,c2wasm_set_object_prop_null,(c2wasm_js_var stack_index, const char *prop_name), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    object[prop_name_formatted] = null;
});

EM_JS(void ,c2wasm_set_object_prop_undefined,(c2wasm_js_var stack_index, const char *prop_name), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    object[prop_name_formatted] = undefined;
});

EM_JS(void,c2wasm_set_object_prop_any,(c2wasm_js_var stack_index, const char *prop_name, int stack_index_value),{
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    object[prop_name_formatted] = window.c2wasm_stack[stack_index_value];
})


EM_JS(void ,private_c2wasm_set_object_prop_function_with_internal_args_raw,(c2wasm_js_var stack_index, const char *prop_name,c2wasm_js_var internal_args, void *callback),{
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let object = window.c2wasm_stack[stack_index];
    let internal_value = window.c2wasm_stack[internal_args];
    object[prop_name_formatted] = window.c2wasm_create_js_c_interop_callback_with_internal_arg(callback,internal_value);
});


EM_JS(void ,private_c2wasm_set_object_prop_function_raw,(c2wasm_js_var stack_index, const char *prop_name, void *callback),{
      let prop_name_formatted = window.c2wasm_get_string(prop_name);
      let object = window.c2wasm_stack[stack_index];
      object[prop_name_formatted] = window.c2wasm_create_js_c_interop_callback(callback);
})
