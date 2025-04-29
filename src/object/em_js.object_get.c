
EM_JS(long ,c2wasm_get_object_prop_long,(long stack_index, const char *prop_name), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    return object[prop_name_formatted];
});

EM_JS(double ,c2wasm_get_object_prop_double,(long stack_index, const char *prop_name), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    return object[prop_name_formatted];
});

EM_JS(long , c2wasm_get_object_prop_any,(long stack_index, const char *prop_name),{
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push(object[prop_name_formatted]);
    return index;
})

EM_JS(int,c2wasm_is_object_prop_true,(long stack_index, const char *prop_name),{
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    return object[prop_name_formatted] == true;
})

EM_JS(int,c2wasm_is_object_prop_undefined,(long stack_index, const char *prop_name),{
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    return object[prop_name_formatted] == undefined;
})

EM_JS(int,c2wasm_is_object_prop_null,(long stack_index, const char *prop_name),{
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    return object[prop_name_formatted] == null;
})

EM_JS(long,c2wasm_call_object_prop,(long stack_index, const char *prop_name,long args),{
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let arguments = undefined;
    if(args != -1){
        arguments = window.c2wasm_stack[args];
    }
    let result = object[prop_name_formatted](...arguments);
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push(result);
    return index;
})