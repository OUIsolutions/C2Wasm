#include "c2wasm.c"
#include <stdio.h>

c2wasm_js_var my_func(){
  printf("Hello from C!\n");
  return 0;
}

int main(){
  c2wasm_start();
  
  c2wasm_js_var my_list = c2wasm_create_array();
  c2wasm_js_var created_callback = c2wasm_create_function(my_func);
  c2wasm_set_array_any_by_index(my_list,0,created_callback);

  c2wasm_set_array_bool_by_index(my_list,1,1);
  c2wasm_set_array_double_by_index(my_list,2,3.14);
  c2wasm_set_array_string_by_index(my_list,3,"hello str setted");
  c2wasm_set_array_long_by_index(my_list,4,123456789); 
  

