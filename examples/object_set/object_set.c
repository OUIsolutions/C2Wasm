#include "c2wasm.c"
#include <stdio.h>



c2wasm_js_var my_func_raw(){
  printf("my func raw called\n");
  return c2wasm_undefined;
}

// in these case, internal args interface its the self object
c2wasm_js_var my_func_with_internal_args_raw(c2wasm_js_var internal_args){
  double test_double = c2wasm_get_object_prop_double(internal_args,"test_double");
  printf("my func with internal args called");
  printf("test_double: %f\n",test_double);
  return c2wasm_undefined;
}

int main(){
  c2wasm_start();
  
  c2wasm_js_var self = c2wasm_create_object();
  c2wasm_set_object_prop_long(self,"test",100);
  c2wasm_set_object_prop_double(self,"test_double",110.0);
  c2wasm_set_object_prop_string(self,"test_string","test");
  c2wasm_set_object_prop_bool(self,"test_bool",1);
  c2wasm_set_object_prop_null(self,"test_null");
  c2wasm_set_object_prop_undefined(self,"test_undefined");
  c2wasm_js_var aray = c2wasm_create_array();
  c2wasm_set_object_prop_any(self,"test_array",aray);

  c2wasm_set_object_prop_function(self,"my_func",my_func_raw);
  c2wasm_set_object_prop_function_with_internal_args(self,"my_func_with_internal_args",self,my_func_with_internal_args_raw);

  c2wasm_set_object_prop_any(c2wasm_window,"created_obj",self);
}