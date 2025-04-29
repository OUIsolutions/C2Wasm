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

EM_JS(long,c2wasm_create_long,(long value),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push(value);
    return index;
});

EM_JS(long,c2wasm_create_double,(double value),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push(value);
    return index;
});

EM_JS(long,c2wasm_create_object,(void),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push({});
    return index;
});

EM_JS(long,c2wasm_create_array,(void),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push([]);
    return index;
});

EM_JS(long,c2wasm_create_string,(const char *value),{
    let index = window.c2wasm_stack.length;
    window.c2wasm_stack.push(value);
    return index;
});