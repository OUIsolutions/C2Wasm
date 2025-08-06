//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.macro.h"
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

EM_JS(long, c2wasm_get_var_long, (c2wasm_js_var stack_index), {
    let value = window.c2wasm_stack[stack_index];
    return value;
});

EM_JS(int, c2wasm_get_var_string_len, (c2wasm_js_var stack_index), {
    let value = window.c2wasm_stack[stack_index];
    return value.length;
});

EM_JS(void *, c2wasm_var_memcpy_string, (c2wasm_js_var stack_index, int start_string, char *dest, int size), {
    let value = window.c2wasm_stack[stack_index];
    for(let i = 0; i < size; i++){
        let current_char = value.charCodeAt(i+start_string);
        if(isNaN(current_char)){
            break;
        }
        wasmExports.c2wasm_set_char(dest,i,current_char);
    }
    return dest;
});

EM_JS(double, c2wasm_get_var_double, (c2wasm_js_var stack_index), {
    let value = window.c2wasm_stack[stack_index];
    return value;
});

EM_JS(int, c2wasm_get_var_type, (c2wasm_js_var stack_index), {
    let value = window.c2wasm_stack[stack_index];
    return window.c2wasm_get_type(value);
});

EM_JS(int, c2wasm_instance_of, (c2wasm_js_var stack_index,c2wasm_js_var target), {
    let value = window.c2wasm_stack[stack_index];
    let target_value = window.c2wasm_stack[target];
    return value instanceof target_value ? 1 : 0;
});

EM_JS(int, c2wasm_get_var_bool, (c2wasm_js_var stack_index), {
    let value = window.c2wasm_stack[stack_index];
    if(value == false){
        return 0;
    }
    return 1;
});

EM_JS(c2wasm_js_var, c2wasm_get_var_any, (c2wasm_js_var stack_index), {
    let value = window.c2wasm_stack[stack_index];
    
    if(value == false){
        return window.c2wasm_false;
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

EM_JS(c2wasm_js_var, c2wasm_call_var, (c2wasm_js_var stack_index, c2wasm_js_var args), {
    let func = window.c2wasm_stack[stack_index];
    let arguments = undefined;
    if(args != -1){
        arguments = window.c2wasm_stack[args];
    }
    let result = null;
    try{
        result = func(...arguments);
    }catch(error){
        result = error;
    }

    if(result == false){
        return window.c2wasm_false;
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
});

EM_JS(c2wasm_js_var, async_c2wasm_call_var, (c2wasm_js_var stack_index, c2wasm_js_var args), {
    let func = window.c2wasm_stack[stack_index];
    let arguments = undefined;
    if(args != -1){
        arguments = window.c2wasm_stack[args];
    }
    let result = null;
   
    (async function(){
        try{
            result = await func(...arguments);
        }catch(error){
            result = error;
        }     
    })();

    if(result == false){
        return window.c2wasm_false;
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
});


