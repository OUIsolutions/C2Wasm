# C2Wasm
A ecmmscripten facilitator to wasm , allowing to control js inside c ,making easier to 
make  frontend applications directly in  C 

## Getting Started 

- 1 Install [ecmmscripten](https://github.com/emscripten-core/emsdk) 
  if you prefer, here its a [quick install setup](https://github.com/mateusmoutinho/emscripten-easy-install)

- 2 download [c2wasm.c](https://github.com/OUIsolutions/C2Wasm/releases/download/0.1.0/c2wasm.c) and save it in a folder 
- 3 create a **test.c** with a callback function, and save into the same dir you saved [c2wasm.c](https://github.com/OUIsolutions/C2Wasm/releases/download/0.1.0/c2wasm.c) 
~~~c 
#include "c2wasm.c"
#include <stdio.h>

long set_div_value(){

  c2wasm_js_var find_args = c2wasm_create_array();
  c2wasm_append_array_string(find_args,"test_div");
  c2wasm_js_var element = c2wasm_call_object_prop(c2wasm_document,"getElementById",find_args);  
  c2wasm_set_object_prop_string(element,"innerHTML","Hello World from C");
  
  return c2wasm_undefined;
}


int main(){
  c2wasm_start();
  c2wasm_set_object_prop_function(c2wasm_window,"set_div_value",set_div_value);
}
~~~
- 4 Compile the test.c with: 
~~~bash
emcc test.c -o test.js
~~~

- 5 create a html file to call our code
~~~html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <script src="test.js"></script>
</head>
<body>
   <div id="test_div"> Old texto</div> 
   <button onclick="set_div_value()">Set div value</button>
</body>
</html>
~~~
- 6 you will need to setup a server , since web assembly requires a server to work.
if you have python on your machine you can start with:

~~~bash
python3 -m http.server 8080
~~~
and if you navegate to **http://localhost:8080/teste.html** , you will se the nasm page.
Alternativly , if you dont have python , on your machine, you can use [yahr](https://github.com/OUIsolutions/yahr), and start the server with:

~~~bash
yahr
~~~