//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.macro.h"
//silver_chain_scope_end



/*    _____   ______            ______                                   __      __                     
   /     | /      \          /      \                                 /  |    /  |                    
   $$$$$ |/$$$$$$  |        /$$$$$$  |  ______    ______    ______   _$$ |_   $$/   ______   _______  
      $$ |$$ \__$$/  ______ $$ |  $$/  /      \  /      \  /      \ / $$   |  /  | /      \ /       \ 
 __   $$ |$$      \ /      |$$ |      /$$$$$$  |/$$$$$$  | $$$$$$  |$$$$$$/   $$ |/$$$$$$  |$$$$$$$  |
/  |  $$ | $$$$$$  |$$$$$$/ $$ |   __ $$ |  $$/ $$    $$ | /    $$ |  $$ | __ $$ |$$ |  $$ |$$ |  $$ |
$$ \__$$ |/  \__$$ |        $$ \__/  |$$ |      $$$$$$$$/ /$$$$$$$ |  $$ |/  |$$ |$$ \__$$ |$$ |  $$ |
$$    $$/ $$    $$/         $$    $$/ $$ |      $$       |$$    $$ |  $$  $$/ $$ |$$    $$/ $$ |  $$ |
 $$$$$$/   $$$$$$/           $$$$$$/  $$/        $$$$$$$/  $$$$$$$/    $$$$/  $$/  $$$$$$/  $$/   $$/ 
                                                                                                      
*/

EM_JS(c2wasm_js_var,c2wasm_create_bool,(int value),{
    let index = window.c2wasm_get_stack_point();
    if (value == 0){
        window.c2wasm_stack[index] = false;
    }
    if (value > 0){
        window.c2wasm_stack[index] = true;
    }
    return index;
});

EM_JS(c2wasm_js_var,c2wasm_create_long,(long value),{
    let index = window.c2wasm_get_stack_point();
    window.c2wasm_stack[index] = value;
    return index;
});

EM_JS(c2wasm_js_var,c2wasm_create_double,(double value),{
    let index = window.c2wasm_get_stack_point();
    window.c2wasm_stack[index] = value;
    return index;
});

EM_JS(c2wasm_js_var,c2wasm_create_object,(void),{
    let index = window.c2wasm_get_stack_point();
    window.c2wasm_stack[index] = {};
    return index;
});

EM_JS(c2wasm_js_var,c2wasm_create_array,(void),{
    let index = window.c2wasm_get_stack_point();
    window.c2wasm_stack[index] = [];
    return index;
});

EM_JS(c2wasm_js_var,c2wasm_create_string,(const char *value),{
    let index = window.c2wasm_get_stack_point();
    window.c2wasm_stack[index] = window.c2wasm_get_string(value);
    return index;
});

EM_JS(c2wasm_js_var,c2wasm_create_function_with_internal_argsraw,(c2wasm_js_var internal_args, void *callback),{
    let internal_value = window.c2wasm_stack[internal_args];
    let index = window.c2wasm_get_stack_point();
    window.c2wasm_stack[index] =  window.c2wasm_create_js_c_interop_callback_with_internal_arg(callback,internal_value);
    return index;
});


EM_JS(c2wasm_js_var,c2wasm_create_function_raw,(void *callback),{
    let index = window.c2wasm_get_stack_point();
    window.c2wasm_stack[index] = window.c2wasm_create_js_c_interop_callback(callback);
    return index;
});

