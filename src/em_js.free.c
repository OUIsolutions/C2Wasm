EM_JS(void,c2wasm_free,(long stack_index),{
    if(window.c2wasm_stack.length <= stack_index){
        return;
    }
    if(window.c2wasm_local_stack){
        //itremove the stack index from old_created obj
        let index_of_stack = window.c2wasm_local_stack.indexOf(stack_index);
        window.c2wasm_local_stack.splice(index_of_stack, 1);
    }
    delete window.c2wasm_stack[stack_index];
});
