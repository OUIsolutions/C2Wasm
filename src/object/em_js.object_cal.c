//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.macro.h"
//silver_chain_scope_end
//
// Created by mateus on 06/08/25.
//

EM_JS(c2wasm_js_var,c2wasm_call_object_prop,(c2wasm_js_var stack_index, const char *prop_name,c2wasm_js_var args),{
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let arguments_callback = null;
    if(args < 0){
        arguments_callback = [];
    }
    else{
        arguments_callback = window.c2wasm_stack[args];
        if(!Array.isArray(arguments_callback)){
            arguments_callback = [arguments_callback];
        }
    }
    let result = null;
    try{
        result = object[prop_name_formatted](...arguments_callback);
    }catch(error){
        result = error;
    }

    if(result === false){
        return  window.c2wasm_false;
    }
    if(result === true){
        return window.c2wasm_true;
    }
    if(result === null){
        return window.c2wasm_null;
    }
    if(result === undefined){
        return window.c2wasm_undefined;
    }
    let created_index = window.c2wasm_get_stack_point();
    window.c2wasm_stack[created_index] = result;
    return created_index;
});

EM_JS(c2wasm_js_var,c2wasm_call_object_constructor,(c2wasm_js_var stack_index, const char *prop_name,c2wasm_js_var args),{
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let arguments_callback = null;
    if(args < 0){
        arguments_callback = [];
    }
    else{
        arguments_callback = window.c2wasm_stack[args];
        if(!Array.isArray(arguments_callback)){
            arguments_callback = [arguments_callback];
        }
    }
    let result = null;
    try{
        result = new object[prop_name_formatted](...arguments_callback);
    }catch(error){
        result = error;
    }

    if(result === false){
        return  window.c2wasm_false;
    }
    if(result === true){
        return window.c2wasm_true;
    }
    if(result === null){
        return window.c2wasm_null;
    }
    if(result === undefined){
        return window.c2wasm_undefined;
    }
    let created_index = window.c2wasm_get_stack_point();
    window.c2wasm_stack[created_index] = result;
    return created_index;
});



#ifdef C2WASM_ALLOW_ASYNC


EM_ASYNC_JS(c2wasm_js_var,await_c2wasm_call_object_prop,(c2wasm_js_var stack_index, const char *prop_name,c2wasm_js_var args),{
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let arguments_callback = null;
    if(args < 0){
        arguments_callback = [];
    }
    else{
        arguments_callback = window.c2wasm_stack[args];
        if(!Array.isArray(arguments_callback)){
            arguments_callback = [arguments_callback];
        }
    }
    let result = null;
    try{
        result = await object[prop_name_formatted](...arguments_callback);
    }catch(error){
        result = error;
    }

    if(result === false){
        return  window.c2wasm_false;
    }
    if(result === true){
        return window.c2wasm_true;
    }
    if(result === null){
        return window.c2wasm_null;
    }
    if(result === undefined){
        return window.c2wasm_undefined;
    }
    let created_index = window.c2wasm_get_stack_point();
    window.c2wasm_stack[created_index] = result;
    return created_index;
});
#endif // C2WASM_ALLOW_ASYNC