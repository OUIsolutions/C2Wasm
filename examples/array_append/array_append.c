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
  c2wasm_append_array_any(my_list,created_callback);
  
  c2wasm_append_array_bool(my_list,1);
  c2wasm_append_array_double(my_list,3.14);
  c2wasm_append_array_string(my_list,"hello");
  c2wasm_append_array_long(my_list,123456789); 
  





  c2wasm_set_object_prop_any(c2wasm_window,"created_array",my_list);

}