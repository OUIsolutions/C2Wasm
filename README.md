# C2Wasm
A ecmmscripten facilitator to wasm , allowing to control js inside c 

## Most simple example 

~~~c 

#include "c2wasm.c"

int main(){
  c2wasm_start();

  c2wasm_set_int_prop(&c2wasm_window, "teste", 33);
  c2wasm_set_string_prop(&c2wasm_window, "teste2", "hello world");
}
~~~
