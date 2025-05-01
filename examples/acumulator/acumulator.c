#include "c2wasm.c"
#include <stdio.h>
c2wasm_js_var add_value(c2wasm_js_var self){
  if(c2wasm_get_array_type_by_index(c2wasm_arguments,0) != C2WASM_NUMBER_TYPE){

    c2wasm_js_var error_args = c2wasm_create_array();
    c2wasm_append_array_string(error_args,"Error: second argument must be a number");
    return c2wasm_call_object_prop(c2wasm_window,"Error",error_args);
  }

  long old_value = c2wasm_get_object_prop_long(self,"value");
  long new_value = old_value + c2wasm_get_array_long_by_index(c2wasm_arguments,0);
  c2wasm_set_object_prop_long(self,"value",new_value);
  return c2wasm_create_long(new_value);
}
c2wasm_js_var create_acmulator(){
  c2wasm_js_var self = c2wasm_create_object();
  c2wasm_set_object_prop_long(self,"value",0);
  c2wasm_set_object_prop_function_with_internal_args(self,"add",self,add_value);
  return self;
}


int main(){
  c2wasm_start();
  c2wasm_set_object_prop_function(c2wasm_window,"create_acumulator",create_acmulator);
}