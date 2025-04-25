#include  "emcc_exports.h"


EM_JS(void ,c2wasm_start_stack, (void), {
 
   if(window['c2wasm_stack'] == undefined){
      window['c2wasm_stack'] = [[window]];
   }

});