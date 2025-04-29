#include "c2wasm.c"

long add(){
    double a = c2wasm_get_array_double_by_index(c2wasm_arguments,0);
    double b = c2wasm_get_array_double_by_index(c2wasm_arguments,1);
    long result = c2wasm_create_double(a + b+300);
    return result; 
}

int main(){
  c2wasm_start();
  //set add as a global function
  c2wasm_set_object_prop_function(c2wasm_window, "add",add);

}