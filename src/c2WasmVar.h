#include  "emcc_exports.h"

typedef struct C2wasmVar {
  long  stack_index;
  long internal_stack_index;
} C2wasmVar;


EMSCRIPTEN_KEEPALIVE long  C2wasmVar_get_stack_index(C2wasmVar *js_var) {
  return js_var->stack_index;
}
EMSCRIPTEN_KEEPALIVE long  C2wasmVar_get_internal_stack_index(C2wasmVar *js_var) {
  return js_var->internal_stack_index;
}