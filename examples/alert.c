#include "c2wasm.c"



int main(){
  c2wasm_start();
  c2wasm_var alert_args = c2wasm_create_array();
  c2wasm_append_array_string(alert_args,"hello from c");
  c2wasm_call_object_prop(c2wasm_window,"alert",alert_args);
}