//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
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


EM_JS(int ,c2wasm_get_object_string_len_prop,(c2wasm_js_var stack_index, const char *prop_name), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let value = object[prop_name_formatted];
    return value.length;
});


EM_JS(void *,c2wams_object_memcpy_string,(c2wasm_js_var stack_index, const char *prop_name, int start_string, char *dest, int size), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let value = object[prop_name_formatted];
    for(let i = 0; i < size; i++){
        let current_char = value.charCodeAt(i+start_string);
        if(isNaN(current_char)){
            break;
        }
        wasmExports.c2wasm_set_char(dest,i,current_char);
    }
    return dest;
});


EM_JS(double ,c2wasm_get_object_prop_double,(c2wasm_js_var stack_index, const char *prop_name), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    return object[prop_name_formatted];
});

EM_JS(int ,c2wasm_get_object_prop_type,(c2wasm_js_var stack_index, const char *prop_name),{
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let value = object[prop_name_formatted];
    return window.c2wasm_get_type(value);
});

EM_JS(int ,c2wasm_get_object_prop_bool,(c2wasm_js_var stack_index, const char *prop_name),{
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let value = object[prop_name_formatted];
    if(value === false){
        return 0;
    }

    return 1;

});

EM_JS(c2wasm_js_var , c2wasm_get_object_prop_any,(c2wasm_js_var stack_index, const char *prop_name),{
    let object = window.c2wasm_stack[stack_index];

    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let value  = object[prop_name_formatted];
    if(value === false){
        return  window.c2wasm_false;
    }
    if(value === true){
        return window.c2wasm_true;
    }
    if(value === null){
        return window.c2wasm_null;
    }
    if(value === undefined){
        return window.c2wasm_undefined;
    }

    let created_index = window.c2wasm_get_stack_point();
    window.c2wasm_stack[created_index] = value;
    return created_index;
    
});


