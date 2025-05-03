#include "c2wasm.c"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    c2wasm_start();
    c2wasm_js_var test_str  = c2wasm_get_object_prop_any(c2wasm_window,"test_str");
    long size = c2wasm_get_string_len(test_str);
    char *buffer = malloc(size+1);
    c2wasm_memcpy_string(test_str,1,buffer,size);
    buffer[size] = '\0';
    printf("str in c:(%s) \n",buffer);
    free(buffer);
    return 0;
}