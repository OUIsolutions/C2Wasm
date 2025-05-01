# Array Iteration in C2Wasm

This guide explains how to work with and iterate over arrays in C2Wasm, using the example from `examples/array_iteration/array_iteration.c`. It covers the relevant C2Wasm API functions, provides a step-by-step breakdown of the example code, and highlights best practices for handling arrays in a C-to-WebAssembly context.

---

## Introduction

C2Wasm allows C code to interact with JavaScript objects and arrays when compiled to WebAssembly. Iterating over arrays is a common operation, and C2Wasm provides a set of API functions to safely access array elements, their types, and values, even when arrays may contain mixed types (numbers, strings, booleans, etc.).

---

## Example: Iterating Over an Array

Below is the core function from the example:

```c
c2wasm_js_var print_elements_of_array(){
  if(c2wasm_get_array_type_by_index(c2wasm_arguments,0) != C2WASM_ARRAY_TYPE){
    c2wasm_js_var error_args = c2wasm_create_array();
    c2wasm_append_array_string(error_args,"Error: first argument must be an array");
    return c2wasm_call_object_prop(c2wasm_window,"Error",error_args);
  }
  c2wasm_js_var arr = c2wasm_get_array_any_by_index(c2wasm_arguments,0);
  long size = c2wasm_get_array_size(arr);
  for(int i = 0; i < size; i++){
      int type = c2wasm_get_array_type_by_index(arr, i);
      if(type == C2WASM_STRING_TYPE){
        int str_size = c2wasm_get_array_string_size_by_index(arr,i);
        char buffer[str_size+1];
        c2wasm_array_memcpy_string(arr,i,0,buffer,str_size);
        buffer[str_size] = '\0';
        printf("[%d]: %s\n", i, buffer);
      }
      if(type == C2WASM_NUMBER_TYPE){
        double value = c2wasm_get_array_double_by_index(arr,i,NULL,0);
        printf("[%d]: %f\n", i, value);
      }
      if(type == C2WASM_BOOLEAN_TYPE){
        int value = c2wasm_get_array_long_by_index(arr,i);
        printf("[%d]: %s\n", i, value ? "true" : "false");
      }
      if(type == C2WASM_NULL_TYPE){
        printf("[%d]: null\n", i);
      }
      if(type == C2WASM_UNDEFINED_TYPE){
        printf("[%d]: undefined\n", i);
      }
  }
  return c2wasm_undefined;
}
```

### Step-by-Step Breakdown

1. **Type Checking:**
   - The function first checks if the first argument is an array using `c2wasm_get_array_type_by_index`.
   - If not, it returns an error.

2. **Array Access:**
   - Retrieves the array argument: `c2wasm_get_array_any_by_index`.
   - Gets the array size: `c2wasm_get_array_size`.

3. **Iteration:**
   - Loops from `0` to `size-1`.
   - For each index, determines the element type using `c2wasm_get_array_type_by_index`.

4. **Element Handling:**
   - **String:**
     - Gets string size: `c2wasm_get_array_string_size_by_index`.
     - Copies string data: `c2wasm_array_memcpy_string`.
     - Prints the string.
   - **Number:**
     - Gets value as double: `c2wasm_get_array_double_by_index`.
     - Prints the number.
   - **Boolean:**
     - Gets value as long: `c2wasm_get_array_long_by_index`.
     - Prints `true` or `false`.
   - **Null/Undefined:**
     - Prints `null` or `undefined`.

5. **Return:**
   - Returns `c2wasm_undefined` to signal completion.

---

## C2Wasm Array API Reference

- `c2wasm_get_array_type_by_index(array, index)`
  - Returns the type of the element at `index` (e.g., `C2WASM_STRING_TYPE`, `C2WASM_NUMBER_TYPE`).
- `c2wasm_get_array_any_by_index(array, index)`
  - Retrieves an element as a generic JS variable.
- `c2wasm_get_array_size(array)`
  - Returns the length of the array.
- `c2wasm_get_array_string_size_by_index(array, index)`
  - Returns the length of a string element.
- `c2wasm_array_memcpy_string(array, index, src_offset, dest_buffer, length)`
  - Copies a string element into a C buffer.
- `c2wasm_get_array_double_by_index(array, index, NULL, 0)`
  - Retrieves a number element as a double.
- `c2wasm_get_array_long_by_index(array, index)`
  - Retrieves a boolean element as a long (0 or 1).

---

## Full Annotated Example

```c
// ...
c2wasm_js_var print_elements_of_array(){
  // Check if the argument is an array
  if(c2wasm_get_array_type_by_index(c2wasm_arguments,0) != C2WASM_ARRAY_TYPE){
    // Error handling
    c2wasm_js_var error_args = c2wasm_create_array();
    c2wasm_append_array_string(error_args,"Error: first argument must be an array");
    return c2wasm_call_object_prop(c2wasm_window,"Error",error_args);
  }
  // Get the array argument
  c2wasm_js_var arr = c2wasm_get_array_any_by_index(c2wasm_arguments,0);
  long size = c2wasm_get_array_size(arr);
  // Iterate over the array
  for(int i = 0; i < size; i++){
      int type = c2wasm_get_array_type_by_index(arr, i);
      if(type == C2WASM_STRING_TYPE){
        int str_size = c2wasm_get_array_string_size_by_index(arr,i);
        char buffer[str_size+1];
        c2wasm_array_memcpy_string(arr,i,0,buffer,str_size);
        buffer[str_size] = '\0';
        printf("[%d]: %s\n", i, buffer);
      }
      if(type == C2WASM_NUMBER_TYPE){
        double value = c2wasm_get_array_double_by_index(arr,i,NULL,0);
        printf("[%d]: %f\n", i, value);
      }
      if(type == C2WASM_BOOLEAN_TYPE){
        int value = c2wasm_get_array_long_by_index(arr,i);
        printf("[%d]: %s\n", i, value ? "true" : "false");
      }
      if(type == C2WASM_NULL_TYPE){
        printf("[%d]: null\n", i);
      }
      if(type == C2WASM_UNDEFINED_TYPE){
        printf("[%d]: undefined\n", i);
      }
  }
  return c2wasm_undefined;
}
```

---

## Best Practices and Notes

- **Type Safety:** Always check the type of each element before accessing its value.
- **Buffer Management:** When handling strings, ensure your buffer is large enough and always null-terminate.
- **Mixed-Type Arrays:** JavaScript arrays can contain mixed types; always branch logic based on the element type.
- **Error Handling:** Return informative errors for invalid arguments.
- **WebAssembly Differences:** Unlike standard C arrays, C2Wasm arrays may contain any JS type, so always use the provided API functions rather than direct memory access.

---

## Conclusion

Array iteration in C2Wasm is straightforward with the provided API. By following the example and best practices above, you can safely and efficiently process JavaScript arrays in your C-to-WebAssembly projects.
