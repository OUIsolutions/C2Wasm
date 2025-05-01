//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.macro.h"
//silver_chain_scope_end

/*
    _____                               __                            __     
   /     |                             /  |                          /  |    
   $$$$$ |  _______          _______  _$$ |_     ______    ______   _$$ |_   
      $$ | /       |______  /       |/ $$   |   /      \  /      \ / $$   |  
 __   $$ |/$$$$$$$//      |/$$$$$$$/ $$$$$$/    $$$$$$  |/$$$$$$  |$$$$$$/   
/  |  $$ |$$      \$$$$$$/ $$      \   $$ | __  /    $$ |$$ |  $$/   $$ | __ 
$$ \__$$ | $$$$$$  |        $$$$$$  |  $$ |/  |/$$$$$$$ |$$ |        $$ |/  |
$$    $$/ /     $$/        /     $$/   $$  $$/ $$    $$ |$$ |        $$  $$/ 
 $$$$$$/  $$$$$$$/         $$$$$$$/     $$$$/   $$$$$$$/ $$/          $$$$/  
 
*/

EM_JS(void ,c2wasm_start, (void), {
    
    if (window.c2wasm_started){
        return;
    }

    
    window.c2wasm_started = true;


    window.c2wasm_false = 0;
    window.c2wasm_true = 1;
    window.c2wasm_null = 2;
    window.c2wasm_undefined = 3;


    window.c2wasm_stack = [];
    window.c2wasm_stack[0] = false;
    window.c2wasm_stack[1] = true;
    window.c2wasm_stack[2] = null;
    window.c2wasm_stack[3] = undefined;
    window.c2wasm_stack[4] = arguments;
    window.c2wasm_stack[5] = window;
    window.c2wasm_stack[6] = document;
    window.c2wasm_stack[7] = document.body;


    window.c2wasm_get_string = function(c_str ){
        let str_array  = [];
        let index = 0;
        while (true){
        let current_char = wasmExports.c2wasm_get_char(c_str,index);
        if (current_char == 0){
            break;
        }
        str_array[index] = current_char; 
        index++;
        }
        return String.fromCharCode.apply(null, str_array);
    };
    
    window.c2wasm_get_stack_point = function(){
        for(let i= 8; i < window.c2wasm_stack.length; i++){
            if (window.c2wasm_stack[i] == undefined){
                if(window.c2wasm_local_stack){
                    window.c2wasm_local_stack.push(i);
                }
                window.c2wasm_stack[i] = 0;
                return i;
            }
        }
        window.c2wasm_stack.push(0);
        let created_index = window.c2wasm_stack.length - 1;
        if(window.c2wasm_local_stack){
            window.c2wasm_local_stack.push(created_index);
        }
        return created_index;
    };
    window.c2wasm_create_js_c_interop_callback_with_internal_arg = function(callback,internal_value){
        return function(){
            let ARGUMENTS_STACK_INDEX = 4;
            let old_arguments = window.c2wasm_stack[ARGUMENTS_STACK_INDEX];
            window.c2wasm_stack[ARGUMENTS_STACK_INDEX] = arguments;
  
            let old_local_stack = window.c2wasm_local_stack;
            let current_local_stack = [];
            window.c2wasm_local_stack = current_local_stack;
            


            let new_interal_args_index = window.c2wasm_get_stack_point();
            window.c2wasm_stack[new_interal_args_index] = internal_value;
            
            let return_index = wasmExports.c2wasm_call_c_function_with_internal_args(new_interal_args_index,callback);
            let return_value = window.c2wasm_stack[return_index];
            
            for(let i = 0; i < current_local_stack.length; i++){
              let item_to_remove_from_stack = current_local_stack[i];
              delete window.c2wasm_stack[item_to_remove_from_stack];
            }
           
            window.c2wasm_stack[ARGUMENTS_STACK_INDEX] = old_arguments;
            window.c2wasm_local_stack = old_local_stack;

            if (return_value instanceof Error){
                throw return_value;
            }
            return return_value;
        };
    };
    window.c2wasm_create_js_c_interop_callback = function(callback){        

        return function(){
            let ARGUMENTS_STACK_INDEX = 4;
            let old_arguments = window.c2wasm_stack[ARGUMENTS_STACK_INDEX];
            window.c2wasm_stack[ARGUMENTS_STACK_INDEX] = arguments;
  
            let old_local_stack = window.c2wasm_local_stack;
            let current_local_stack = [];
            window.c2wasm_local_stack = current_local_stack;
        
            let return_index = wasmExports.c2wasm_call_c_function(callback);
            let return_value = window.c2wasm_stack[return_index];
            
            for(let i = 0; i < current_local_stack.length; i++){
              let item_to_remove_from_stack = current_local_stack[i];
              delete window.c2wasm_stack[item_to_remove_from_stack];
            }
           
            window.c2wasm_stack[ARGUMENTS_STACK_INDEX] = old_arguments;
            window.c2wasm_local_stack = old_local_stack;

            if( return_value instanceof Error){
                throw return_value;
            }
            return return_value;
        };
    };

});