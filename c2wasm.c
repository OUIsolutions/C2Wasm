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



typedef struct C2wasmVar {
  long  stack_index;
  long internal_stack_index;
} C2wasmVar;


EMSCRIPTEN_KEEPALIVE long  C2wasmVar_get_stack_index(C2wasmVar *js_var) {
  return js_var->stack_index;
}
EMSCRIPTEN_KEEPALIVE long  C2wasmVar_get_internal_stack_index(C2wasmVar *js_var) {
  return js_var->internal_stack_index;
}


C2wasmVar c2wasm_window = {0, 0};


EMSCRIPTEN_KEEPALIVE char c2wasm_get_char(const char *str,int index) {
    return str[index];
}



EM_JS(void ,c2wasm_start, (void), {
 
   if(window['c2wasm_stack'] == undefined){
      window['c2wasm_stack'] = [[window]];

      window['c2wasm_get_string'] = function(c_str ){
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
   }
});


EM_JS(void ,c2wasm_set_int_prop,(C2wasmVar *js_var,const char *prop_name, int value), {
    let stack_index = wasmExports.C2wasmVar_get_stack_index(js_var);
    let internal_stack_index = wasmExports.C2wasmVar_get_internal_stack_index(js_var);
    let object = window['c2wasm_stack'][stack_index][internal_stack_index];
    let prop_name_formatted = c2wasm_get_string(prop_name);
    object[prop_name_formatted] = value;
});

EM_JS(void ,c2wasm_set_float_prop,(C2wasmVar *js_var,const char *prop_name, float value), {
    let stack_index = wasmExports.C2wasmVar_get_stack_index(js_var);
    let internal_stack_index = wasmExports.C2wasmVar_get_internal_stack_index(js_var);
    let object = window['c2wasm_stack'][stack_index][internal_stack_index];
    let prop_name_formatted = c2wasm_get_string(prop_name);
    object[prop_name_formatted] = value;
});

EM_JS(void ,c2wasm_set_string_prop,(C2wasmVar *js_var,const char *prop_name, const char *value), {
    let stack_index = wasmExports.C2wasmVar_get_stack_index(js_var);
    let internal_stack_index = wasmExports.C2wasmVar_get_internal_stack_index(js_var);
    let object = window['c2wasm_stack'][stack_index][internal_stack_index];
    let prop_name_formatted = c2wasm_get_string(prop_name);
    let value_formatted = c2wasm_get_string(value);
    object[prop_name_formatted] = value_formatted;
});
EM_JS(void ,c2wasm_set_bool_prop,(C2wasmVar *js_var,const char *prop_name, int value), {
    let stack_index = wasmExports.C2wasmVar_get_stack_index(js_var);
    let internal_stack_index = wasmExports.C2wasmVar_get_internal_stack_index(js_var);
    let object = window['c2wasm_stack'][stack_index][internal_stack_index];
    let prop_name_formatted = c2wasm_get_string(prop_name);
    object[prop_name_formatted] = value;
});



EM_JS(void ,c2wasm_set_function_prop,(C2wasmVar *js_var,const char *prop_name, C2wasmVar (*callback)(int stack_index) ){

    window['c2wasm_stack'].push([]);
    let index = window['c2wasm_stack'].length;
    //dostuf
    console.log("callback",callback);

    window['c2wasm_stack'].pop();

});

#endif // __c2wasm_c__