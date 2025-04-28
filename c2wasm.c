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
long c2wasm_window = 3;
long c2wasm_document = 4;
long c2wasm_body  = 5;


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
})

EM_JS(void,c2wasm_create_double,(double value),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push(value);
    return index;
})

EM_JS(void,c2wasm_create_object,(void),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push({});
    return index;
})

EM_JS(void,c2wasm_create_array,(void),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push([]);
    return index;
})

EM_JS(void,c2wasm_create_string,(const char *value),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push(value);
    return index;
})
//bool,true,null and undefined its not necessary since they are already defined

//==================================JS Object Props ========================================================

EM_JS(void ,c2wasm_set_int_prop,(long stack_index, const char *prop_name, int value), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    object[prop_name_formatted] = value;
});

EM_JS(void ,c2wasm_set_float_prop,(long stack_index, const char *prop_name, float value), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    object[prop_name_formatted] = value;
});

EM_JS(void ,c2wasm_set_string_prop,(long stack_index, const char *prop_name, const char *value), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let value_formatted = window.c2wasm_get_string(value);
    object[prop_name_formatted] = value_formatted;
});
EM_JS(void ,c2wasm_set_bool_prop,(long stack_index, const char *prop_name, int value), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    object[prop_name_formatted] = value;
});

EM_JS(void ,c2wasm_set_null_prop,(long stack_index, const char *prop_name), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    object[prop_name_formatted] = null;
});

EM_JS(void ,c2wasm_set_undefined_prop,(long stack_index, const char *prop_name), {
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    object[prop_name_formatted] = undefined;
});

EM_JS(void,c2wasm_set_any_prop,(long stack_index, const char *prop_name, int stack_index_value),{
    let object = window.c2wasm_stack[stack_index];
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    object[prop_name_formatted] = window.c2wasm_stack[stack_index_value];
})


//==============================METHODS===================================================================


EM_JS(void ,c2wasm_set_method,(long stack_index, const char *prop_name, void *callback),{

    //dostuf
    let prop_name_formatted = window.c2wasm_get_string(prop_name);
    let object = window.c2wasm_stack[stack_index];
    
    object[prop_name_formatted] = function(args){

        int return_index = wasmExports.c2wasm_call_c_function(callback);
        return window.c2wasm_stack[return_index];
    }

});

#endif // __c2wasm_c__