#include "c2wasm.c"
#include <stdio.h>

// Função que itera sobre um array recebido como argumento
c2wasm_js_var print_elements_of_array(){
  if(c2wasm_get_array_type_by_index(c2wasm_arguments,0) != C2WASM_ARRAY_TYPE){
    c2wasm_js_var error_args = c2wasm_create_array();
    c2wasm_append_array_string(error_args,"Error: first argument must be an array");
    return c2wasm_call_object_prop(c2wasm_window,"Error",error_args);
  }
  c2wasm_js_var arr = c2wasm_get_array_any_by_index(c2wasm_arguments,0);
  long size = c2wasm_get_array_size(arr);
  for(int i = 0; i < size; i++){
      int type = c2wasm_get_array_type_by_index(arr, i);
      if(type == C2WASM_STRING_TYPE){
        int str_size = c2wasm_get_array_string_size_by_index(arr,i);
        char buffer[str_size+1];
        c2wasm_array_memcpy_string(arr,i,0,buffer,str_size);
        buffer[str_size] = '\0';
        printf("[%d]: %s\n", i, buffer);
      }
      if(type == C2WASM_NUMBER_TYPE){
        double value = c2wasm_get_array_double_by_index(arr,i,NULL,0);
        printf("[%d]: %f\n", i, value);
      }
      if(type == C2WASM_BOOLEAN_TYPE){
        int value = c2wasm_get_array_long_by_index(arr,i);
        printf("[%d]: %s\n", i, value ? "true" : "false");
      }
      if(type == C2WASM_NULL_TYPE){
        printf("[%d]: null\n", i);
      }
      if(type == C2WASM_UNDEFINED_TYPE){
        printf("[%d]: undefined\n", i);
      }
  }
  return c2wasm_undefined;
}

int main(){
  c2wasm_start();
  c2wasm_set_object_prop_function(c2wasm_window,"print_elements_of_array",print_elements_of_array);

  return 0;
}
