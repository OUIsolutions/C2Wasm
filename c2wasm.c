#ifndef __c2wasm_c__
#define __c2wasm_c__

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#ifndef EMSCRIPTEN_KEEPALIVE
#define EMSCRIPTEN_KEEPALIVE
#endif

#ifndef EM_JS
#define EM_JS(ret, name, params, body) ret name params;
#endif

long c2wasm_false  = 0;
long c2wasm_true = 1;
long c2wasm_null = 2;
long c2wasm_undefined = 3;
long c2wasm_arguments = 4;
long c2wasm_window = 5;
long c2wasm_document = 6;
long c2wasm_body  = 7;





//===============================C Functions ========================================================


EMSCRIPTEN_KEEPALIVE char c2wasm_get_char(const char *str,int index) {
    return str[index];
}

EMSCRIPTEN_KEEPALIVE void c2wasm_call_c_function(void *callback){
    void (*converted_callback)() = (void (*)())callback;
    converted_callback();
}
//==================================JS Functions ========================================================
EM_JS(void ,c2wasm_start, (void), {
 

   window.c2wasm_stack = [
      false,
      true,
      null,    
      undefined,
      window,
      document,
      body
   ];
    window.window.c2wasm_get_string = function(c_str ){
        let str_array  = [];
        let index = 0;
        while (true){
        let current_char = wasmExports.c2wasm_get_char(c_str,index);
        if (current_char == 0){
            break;
        }
        str_array[index] = current_char; 
        index++;
        }
        return String.fromCharCode.apply(null, str_array);
    }

});
//==================================JS Creation=============================================================

EM_JS(void,c2wasm_create_long,(long value),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push(value);
    return index;
});

EM_JS(void,c2wasm_create_double,(double value),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push(value);
    return index;
});

EM_JS(void,c2wasm_create_object,(void),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push({});
    return index;
});

EM_JS(void,c2wasm_create_array,(void),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push([]);
    return index;
});

EM_JS(void,c2wasm_create_string,(const char *value),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push(value);
    return index;
});
//bool,true,null and undefined its not necessary since they are already defined
//=================================JS Array Getters=========================================================

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
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push(array[index]);
    return index;
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
//=================================JS Array Setters=========================================================

EM_JS(void ,c2wasm_set_array_long_by_index,(long stack_index, int index, long value), {
    let array = window.c2wasm_stack[stack_index];
    array[index] = value;
});

EM_JS(void ,c2wasm_set_array_double_by_index,(long stack_index, int index, double value), {
    let array = window.c2wasm_stack[stack_index];
    array[index] = value;
});

EM_JS(void ,c2wasm_set_array_any_by_index,(long stack_index, int index, int stack_index_value),{
    let array = window.c2wasm_stack[stack_index];
    array[index] = window.c2wasm_stack[stack_index_value];
})

EM_JS(void ,c2wasm_set_array_index_bool,(long stack_index, int index, int value), {
    let array = window.c2wasm_stack[stack_index];
    if (value == 0){
        array[index] = false;
    }
    if (value > 0){
        array[index] = true;
    }
});

EM_JS(void ,c2wasm_set_array_index_null,(long stack_index, int index), {
    let array = window.c2wasm_stack[stack_index];
    array[index] = null;
});

EM_JS(void ,c2wasm_set_array_index_undefined,(long stack_index, int index), {
    let array = window.c2wasm_stack[stack_index];
    array[index] = undefined;
});


//==================================JS Object Getters=======================================================

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
//==================================JS Object Seters ========================================================

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


EM_JS(void ,c2wasm_set_method,(long stack_index, const char *prop_name, void *callback),{

    //dostuf
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let object = window.c2wasm_stack[stack_index];
    let ARGUMENTS_STACK_INDEX = 4;
    object[prop_name_formatted] = function(){
        let old_arguments = window.c2wasm_stack[ARGUMENTS_STACK_INDEX];
        window.c2wasm_stack[ARGUMENTS_STACK_INDEX] = arguments;
        let return_index = wasmExports.c2wasm_call_c_function(callback);
        window.c2wasm_stack[ARGUMENTS_STACK_INDEX] = old_arguments;
        return window.c2wasm_stack[return_index];
    }

});

#endif // __c2wasm_c__