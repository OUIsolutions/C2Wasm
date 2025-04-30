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

EM_JS(void ,c2wasm_set_object_prop_float,(long stack_index, const char *prop_name, float value), {
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

EM_JS(void ,c2wasm_set_object_prop_bool,(long stack_index, const char *prop_name, int value), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    if (value == 0){
        object[prop_name_formatted] = false;
    }
    if (value > 0){
        object[prop_name_formatted] = true;
    }
});

EM_JS(void ,c2wasm_set_object_prop_null,(long stack_index, const char *prop_name), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    object[prop_name_formatted] = null;
});

EM_JS(void ,c2wasm_set_object_prop_undefined,(long stack_index, const char *prop_name), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    object[prop_name_formatted] = undefined;
});

EM_JS(void,c2wasm_set_object_prop_any,(long stack_index, const char *prop_name, int stack_index_value),{
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    object[prop_name_formatted] = window.c2wasm_stack[stack_index_value];
})


EM_JS(void ,private_c2wasm_set_object_prop_function_with_internal_args_raw,(long stack_index, const char *prop_name,long internal_args, void *callback),{

    //dostuf
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let object = window.c2wasm_stack[stack_index];
    let ARGUMENTS_STACK_INDEX = 4;
    object[prop_name_formatted] = function(){
        let old_arguments = window.c2wasm_stack[ARGUMENTS_STACK_INDEX];
        window.c2wasm_stack[ARGUMENTS_STACK_INDEX] = arguments;
        let old_created_objects = window.c2wasm_old_created_objects;
        window.c2wasm_old_created_objects = [];

        let return_index = wasmExports.c2wasm_call_c_function_with_internal_args(internal_args,callback);
        
       
        
        window.c2wasm_stack[ARGUMENTS_STACK_INDEX] = old_arguments;
        window.c2wasm_old_created_objects = old_created_objects;
        
        return window.c2wasm_stack[return_index];
    }
});


EM_JS(void ,private_c2wasm_set_object_prop_function_raw,(long stack_index, const char *prop_name, void *callback),{
      //dostuf
      let prop_name_formatted = window.c2wasm_get_string(prop_name);
      let object = window.c2wasm_stack[stack_index];
      let ARGUMENTS_STACK_INDEX = 4;
      object[prop_name_formatted] = function(){
          let old_arguments = window.c2wasm_stack[ARGUMENTS_STACK_INDEX];
          let old_created_objects = window.c2wasm_old_created_objects;
            window.c2wasm_old_created_objects = [];
          window.c2wasm_stack[ARGUMENTS_STACK_INDEX] = arguments;
          let return_index = wasmExports.c2wasm_call_c_function(callback);
          window.c2wasm_stack[ARGUMENTS_STACK_INDEX] = old_arguments;
          window.c2wasm_old_created_objects = old_created_objects;
          return window.c2wasm_stack[return_index];
      }
})
