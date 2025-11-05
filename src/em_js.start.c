//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
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
    window.c2wasm_stack[8] = Error;


 window.c2wasm_get_string = function(c_str ){
        let str_array  = [];

        let size = wasmExports.c2wasm_get_str_size(c_str);
        for(let i=0; i < size; i++){
            let current_char = wasmExports.c2wasm_get_char(c_str,i);
            str_array[i] = current_char; 
        }
        //iterate over str_array and print each char 

        let decoder = new TextDecoder('utf-8');
        let uint8Array = new Uint8Array(str_array);
        return decoder.decode(uint8Array);
    };
    
    window.c2wasm_get_stack_point = function(){
        for(let i= 8; i < window.c2wasm_stack.length; i++){
            if (window.c2wasm_stack[i] == undefined){
         
                window.c2wasm_stack[i] = 0;
                return i;
            }
        }
        window.c2wasm_stack.push(0);
        let created_index = window.c2wasm_stack.length - 1;

        return created_index;
    };
    window.c2wasm_create_js_c_interop_callback_with_internal_arg = function(callback,internal_value){
        return function(){
            let ARGUMENTS_STACK_INDEX = 4;
            let old_arguments = window.c2wasm_stack[ARGUMENTS_STACK_INDEX];
            window.c2wasm_stack[ARGUMENTS_STACK_INDEX] = arguments;
  
    


            let new_interal_args_index = window.c2wasm_get_stack_point();
            window.c2wasm_stack[new_interal_args_index] = internal_value;
            
            let return_index = wasmExports.c2wasm_call_c_function_with_internal_args(new_interal_args_index,callback);
            let return_value = window.c2wasm_stack[return_index];
            
         
            window.c2wasm_stack[ARGUMENTS_STACK_INDEX] = old_arguments;

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
  
           
            let return_index = wasmExports.c2wasm_call_c_function(callback);
            let return_value = window.c2wasm_stack[return_index];
            
        
           
            window.c2wasm_stack[ARGUMENTS_STACK_INDEX] = old_arguments;

            if( return_value instanceof Error){
                throw return_value;
            }
            return return_value;
        };
    };
    //check macro.types.h to see the types 
    window.c2wasm_get_type = function(value){
        if(value == undefined){
            return 0;
        };
        if(value == null){
            return 1;
        };
        if(value == true || value == false){
            return 2;
        };
        if(typeof value == "number"){
            return 3;
        };
        if(typeof value == "string"){
            return 4;
        };
        if(Array.isArray(value)){
            return 6;
        };
        if(typeof value == "object"){
            return 5;
        };
        if(typeof value == "function"){
            return 7;
        };
        if(typeof value == "symbol"){
            return 8;
        }
        if(typeof value == "bigint"){
            return 9;
        };
        return -1;
    };
});