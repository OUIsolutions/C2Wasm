#include  "emcc_exports.h"
#include "var.h"


C2wasmVar c2wasm_window = {0, 0};

EM_JS(void ,c2wasm_start_stack, (void), {
 
   if(window['c2wasm_stack'] == undefined){
      window['c2wasm_stack'] = [[window]];
   }

});