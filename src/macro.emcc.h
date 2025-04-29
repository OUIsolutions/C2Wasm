
#ifndef __c2wasm_c__
#define __c2wasm_c__

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#ifndef EMSCRIPTEN_KEEPALIVE
#define EMSCRIPTEN_KEEPALIVE
#endif

#ifndef EM_JS
#define EM_JS(ret, name, params, body) ret name params;
#endif
#ifndef true 
#define true 1
#endif
#ifndef false
#define false 0
#endif


#define c2wasm_js_var long