# Setting Array Properties in C2Wasm

This guide explains how to set and append elements to JavaScript arrays from C code using the C2Wasm framework, based on examples from `examples/array_set/array_set.c` and `examples/array_append/array_append.c`.

## Table of Contents
1. [Introduction](#introduction)
2. [Creating Arrays](#creating-an-array)
3. [Setting Elements](#setting-array-elements-by-index)
4. [Appending Elements](#appending-elements-to-an-array)
5. [API Reference](#c2wasm-array-modification-api-reference)
6. [Best Practices](#best-practices--tips)
7. [See Also](#see-also)

## Introduction

C2Wasm enables C code to create and modify JavaScript arrays when compiled to WebAssembly. This document covers how to create arrays, set elements at specific indices, and append elements to arrays.

## Creating an Array

To create a new array, use the `c2wasm_create_array()` function:

```c
c2wasm_js_var my_list = c2wasm_create_array();
```

This creates an empty JavaScript array that you can then populate with values.

## Setting Array Elements by Index

To set an element at a specific index, use the `c2wasm_set_array_<type>_by_index` functions:

```c
// Create an array
c2wasm_js_var my_list = c2wasm_create_array();

// Create a function to use as an element
c2wasm_js_var created_callback = c2wasm_create_function(my_func);

// Set various types of elements at specific indices
c2wasm_set_array_any_by_index(my_list, 0, created_callback);
c2wasm_set_array_bool_by_index(my_list, 1, 1);  // true
c2wasm_set_array_double_by_index(my_list, 2, 3.14);
c2wasm_set_array_string_by_index(my_list, 3, "hello world");
c2wasm_set_array_long_by_index(my_list, 4, 123456789);
```

### Available Set-by-Index Functions

| Function | Description |
|----------|-------------|
| `c2wasm_set_array_any_by_index(array, index, value)` | Sets any JavaScript value at the specified index |
| `c2wasm_set_array_bool_by_index(array, index, bool_value)` | Sets a boolean value (0 = false, non-zero = true) |
| `c2wasm_set_array_double_by_index(array, index, double_value)` | Sets a floating-point number |
| `c2wasm_set_array_string_by_index(array, index, string_value)` | Sets a string value |
| `c2wasm_set_array_long_by_index(array, index, long_value)` | Sets an integer value |

## Appending Elements to an Array

To add elements to the end of an array, use the `c2wasm_append_array_<type>` functions:

```c
// Create an array
c2wasm_js_var my_list = c2wasm_create_array();

// Create a function to use as an element
c2wasm_js_var created_callback = c2wasm_create_function(my_func);

// Append various types of elements to the array
c2wasm_append_array_any(my_list, created_callback);
c2wasm_append_array_bool(my_list, 1);  // true
c2wasm_append_array_double(my_list, 3.14);
c2wasm_append_array_string(my_list, "hello");
c2wasm_append_array_long(my_list, 123456789);
```

### Available Append Functions

| Function | Description |
|----------|-------------|
| `c2wasm_append_array_any(array, value)` | Appends any JavaScript value |
| `c2wasm_append_array_bool(array, bool_value)` | Appends a boolean value (0 = false, non-zero = true) |
| `c2wasm_append_array_double(array, double_value)` | Appends a floating-point number |
| `c2wasm_append_array_string(array, string_value)` | Appends a string value |
| `c2wasm_append_array_long(array, long_value)` | Appends an integer value |

### Using Arrays with JavaScript Objects

Once you've created and populated an array, you can assign it to a JavaScript object property:

```c
// Make the array accessible globally from JavaScript
c2wasm_set_object_prop_any(c2wasm_window, "created_array", my_list);
```

## C2Wasm Array Modification API Reference

### Creation

| Function | Description |
|----------|-------------|
| `c2wasm_create_array()` | Creates a new empty JavaScript array |

### Modification

| Approach | Function Pattern | Use Case |
|----------|------------------|----------|
| Set by Index | `c2wasm_set_array_*_by_index` | Update or insert at a specific position |
| Append | `c2wasm_append_array_*` | Add new elements to the end of the array |

### Key Differences

| Operation | Overwrites existing? | Behavior with sparse arrays |
|-----------|----------------------|-----------------------------|
| Set by Index | Yes | Creates sparse array when index > length |
| Append | No | Always adds to the end, no gaps |

## Best Practices & Tips

- **Choose Wisely**: Use `set_by_index` for random access updates, `append` for sequential building
- **Sparse Arrays**: When using `set_by_index` with large indices, be aware of memory implications
- **Type Safety**: Use type-specific functions whenever possible
- **Initialization**: Always create the array before attempting to modify it
- **Mixed Operations**: You can freely mix setting and appending operations on the same array

## Complete Example

```c
#include "c2wasm.c"
#include <stdio.h>

c2wasm_js_var my_func() {
  printf("Hello from C!\n");
  return c2wasm_undefined;
}

int main() {
  c2wasm_start();
  
  // Create array
  c2wasm_js_var my_list = c2wasm_create_array();
  c2wasm_js_var created_callback = c2wasm_create_function(my_func);
  
  // Set items by index
  c2wasm_set_array_any_by_index(my_list, 0, created_callback);
  c2wasm_set_array_bool_by_index(my_list, 1, 1);
  c2wasm_set_array_double_by_index(my_list, 2, 3.14);
  c2wasm_set_array_string_by_index(my_list, 3, "hello by index");
  c2wasm_set_array_long_by_index(my_list, 4, 123456789);

  // Append items to the end
  c2wasm_append_array_any(my_list, created_callback); // index 5
  c2wasm_append_array_bool(my_list, 1);              // index 6
  c2wasm_append_array_double(my_list, 3.14);         // index 7
  c2wasm_append_array_string(my_list, "hello");       // index 8
  c2wasm_append_array_long(my_list, 123456789);      // index 9

  // Make array available to JavaScript
  c2wasm_set_object_prop_any(c2wasm_window, "created_array", my_list);
}
```

## See Also

- [Getting Array Properties](./getting_array_props.md)
- [Getting Object Properties](./getting_object_props.md)
- [Setting Object Properties](./setting_object_props.md)
