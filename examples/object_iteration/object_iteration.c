#include "c2wasm.c"
#include <stdio.h>




// in these case, internal args interface its the self object
c2wasm_js_var print_elements_of_object(){

  if(c2wasm_get_array_type_by_index(c2wasm_arguments,0) != C2WASM_OBJECT_TYPE){
    
    c2wasm_js_var error_args = c2wasm_create_array();
    c2wasm_append_array_string(error_args,"Error: first argument must be an object");
    return c2wasm_call_object_prop(c2wasm_window,"Error",error_args);
  }
  c2wasm_js_var current_object = c2wasm_get_array_any_by_index(c2wasm_arguments,0);

 
  c2wasm_js_var Object = c2wasm_get_object_prop_any(c2wasm_window,"Object");
  c2wasm_js_var keys_args = c2wasm_create_array();
  c2wasm_append_array_any(keys_args,current_object);
  c2wasm_js_var keys = c2wasm_call_object_prop(Object,"keys",keys_args);

  long size = c2wasm_get_array_size(keys);
  for(int i = 0; i < size; i++){
      int key_size = c2wasm_get_array_string_size_by_index(keys,i);
      char buffer_key[key_size];
      c2wasm_array_memcpy_string(keys,i,0,buffer_key,key_size);
      buffer_key[key_size] = '\0';
      int value_type = c2wasm_get_object_prop_type(current_object,buffer_key);


      if(value_type == C2WASM_STRING_TYPE){
        int value_size = c2wasm_get_object_string_len_prop(current_object,buffer_key);
        char buffer_value[value_size];
        c2wams_object_memcpy_string(current_object,buffer_key,buffer_value,value_size);
        buffer_value[value_size] = '\0';
        printf("%s: %s\n",buffer_key,buffer_value);
      }

      if(value_type == C2WASM_NUMBER_TYPE){
        double value = c2wasm_get_object_prop_double(current_object,buffer_key);
        printf("%s: %f\n",buffer_key,value);
      }
      if(value_type == C2WASM_BOOLEAN_TYPE){
        int value = c2wasm_get_object_prop_bool(current_object,buffer_key);
        printf("%s: %s\n",buffer_key,value ? "true" : "false");
      }
      if(value_type == C2WASM_NULL_TYPE){
        printf("%s: null\n",buffer_key);
      }
      if(value_type == C2WASM_UNDEFINED_TYPE){
        printf("%s: undefined\n",buffer_key);
      }
  }
  return c2wasm_undefined;

}

int main(){
  c2wasm_start();
  
  
  c2wasm_set_object_prop_function(c2wasm_window,"print_object",print_elements_of_object);
}