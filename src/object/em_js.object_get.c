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
$$ |  $$ | ______  /      \  /      \ / $$   |  
$$ |  $$ |/      |/$$$$$$  |/$$$$$$  |$$$$$$/   
$$ |  $$ |$$$$$$/ $$ |  $$ |$$    $$ |  $$ | __ 
$$ \__$$ |        $$ \__$$ |$$$$$$$$/   $$ |/  |
$$    $$/         $$    $$ |$$       |  $$  $$/ 
 $$$$$$/           $$$$$$$ | $$$$$$$/    $$$$/  
                  /  \__$$ |                    
                  $$    $$/                     
                   $$$$$$/                      

*/

EM_JS(long ,c2wasm_get_object_prop_long,(c2wasm_js_var stack_index, const char *prop_name), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    return object[prop_name_formatted];
});

EM_JS(double ,c2wasm_get_object_prop_double,(c2wasm_js_var stack_index, const char *prop_name), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    return object[prop_name_formatted];
});

EM_JS(c2wasm_js_var , c2wasm_get_object_prop_any,(c2wasm_js_var stack_index, const char *prop_name),{
    let object = window.c2wasm_stack[stack_index];


    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let value  = object[prop_name_formatted];
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
    
})


EM_JS(c2wasm_js_var,c2wasm_call_object_prop,(c2wasm_js_var stack_index, const char *prop_name,c2wasm_js_var args),{
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let arguments = undefined;
    if(args != -1){
        arguments = window.c2wasm_stack[args];
    }
    let result = object[prop_name_formatted](...arguments);
    if(result == false){
        return  window.c2wasm_false;
    }
    if(result == true){
        return window.c2wasm_true;
    }
    if(result == null){
        return window.c2wasm_null;
    }
    if(result == undefined){
        return window.c2wasm_undefined;
    }
    let created_index = window.c2wasm_get_stack_point();
    window.c2wasm_stack[created_index] = result;
    return created_index;
})