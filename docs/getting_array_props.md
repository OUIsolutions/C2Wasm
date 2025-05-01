# Getting Array Properties in C2Wasm

This guide explains how to retrieve and iterate over elements in JavaScript arrays using C2Wasm, based on the example from `examples/array_iteration/array_iteration.c`.

## Table of Contents
1. [Introduction](#introduction)
2. [Step-by-Step Example](#step-by-step-example)
3. [API Reference](#c2wasm-array-api-reference)
4. [Best Practices](#best-practices-and-notes)
5. [See Also](#see-also)

## Introduction

C2Wasm enables C code to interact with JavaScript arrays when compiled to WebAssembly. This document covers how to safely access array elements, determine their types, and retrieve their values, even when arrays contain mixed types.

## Step-by-Step Example

Below is an example function that retrieves and processes array elements:

```c
c2wasm_js_var print_elements_of_array(){
  // Check if first argument is an array
  if(c2wasm_get_array_type_by_index(c2wasm_arguments,0) != C2WASM_ARRAY_TYPE){
    c2wasm_js_var error_args = c2wasm_create_array();
    c2wasm_append_array_string(error_args,"Error: first argument must be an array");
    return c2wasm_call_object_prop(c2wasm_window,"Error",error_args);
  }
  
  // Get the array and its size
  c2wasm_js_var arr = c2wasm_get_array_any_by_index(c2wasm_arguments,0);
  long size = c2wasm_get_array_size(arr);
  
  // Iterate over array elements
  for(int i = 0; i < size; i++){
      int type = c2wasm_get_array_type_by_index(arr, i);
      
      // Handle different types
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

### Key Processing Steps

1. **Type Checking**: Ensure the input is an array
2. **Array Access**: Get the array and determine its size
3. **Iteration**: Loop through each element
4. **Type Detection**: Check the type of each element 
5. **Type-Specific Handling**: Process each element according to its type

## C2Wasm Array API Reference

| Function | Description |
|----------|-------------|
| `c2wasm_get_array_type_by_index(array, index)` | Returns the type of the element at `index` |
| `c2wasm_get_array_any_by_index(array, index)` | Retrieves an element as a generic JS variable |
| `c2wasm_get_array_size(array)` | Returns the length of the array |
| `c2wasm_get_array_string_size_by_index(array, index)` | Returns the length of a string element |
| `c2wasm_array_memcpy_string(array, index, src_offset, dest_buffer, length)` | Copies a string element into a C buffer |
| `c2wasm_get_array_double_by_index(array, index, NULL, 0)` | Retrieves a number element as a double |
| `c2wasm_get_array_long_by_index(array, index)` | Retrieves a boolean element as a long (0 or 1) |

### Type Constants

| Constant | Description |
|----------|-------------|
| `C2WASM_STRING_TYPE` | Element is a string |
| `C2WASM_NUMBER_TYPE` | Element is a number |
| `C2WASM_BOOLEAN_TYPE` | Element is a boolean |
| `C2WASM_NULL_TYPE` | Element is null |
| `C2WASM_UNDEFINED_TYPE` | Element is undefined |
| `C2WASM_ARRAY_TYPE` | Element is an array |
| `C2WASM_OBJECT_TYPE` | Element is an object |

## Best Practices and Notes

- **Type Safety**: Always check element types before accessing values
- **Buffer Management**: For strings, ensure buffers are properly sized and null-terminated
- **Mixed Types**: JavaScript arrays can contain multiple types, so branch logic accordingly
- **Error Handling**: Validate inputs and return informative errors
- **Memory Usage**: Plan for appropriate buffer sizes when dealing with string data
- **Performance**: Consider caching type information when processing large arrays

## See Also

- [Setting Array Properties](./setting_array_props.md)
- [Getting Object Properties](./getting_object_props.md)
- [Setting Object Properties](./setting_object_props.md)
