#ifndef EMSCRIPTEN_KEEPALIVE
#define EMSCRIPTEN_KEEPALIVE
#endif

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif



#ifndef EM_JS
#define EM_JS(ret, name, params, body) ret name params;
#endif
#ifdef __ASYNCIFY__

#ifndef EM_ASYNC_JS
#define EM_ASYNC_JS(ret, name, params, body) ret name params;
#endif
#endif 

#ifndef true 
#define true 1
#endif
#ifndef false
#define false 0
#endif



