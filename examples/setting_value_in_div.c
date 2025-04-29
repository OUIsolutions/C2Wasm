#include "c2wasm.c"



int main(){
  c2wasm_start();
  c2wasm_var find_args = c2wasm_create_array();
  c2wasm_append_array_string(find_args,"test_div");
  c2wasm_var test_div = c2wasm_call_object_prop(c2wasm_document,"getElementById",find_args);
  c2wasm_set_object_prop_string(test_div,"innerHTML","Hello World setted in C");

}