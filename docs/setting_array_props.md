# Setting Array Properties in C2Wasm

This guide details how to set and append array properties when working with arrays in C2Wasm, using the examples from `examples/array_set/array_set.c` and `examples/array_append/array_append.c`.

## Overview
C2Wasm provides a set of functions for interacting with JavaScript-like arrays from C code. You can create arrays, set values at specific indices, or append values to the end of the array. The API supports multiple value types, including functions, booleans, doubles, strings, and longs.

---

## Creating an Array
To create a new array:
```c
c2wasm_js_var my_list = c2wasm_create_array();
```

---

## Setting Array Elements by Index
To set an element at a specific index, use the `c2wasm_set_array_<type>_by_index` functions. These functions overwrite any existing value at the given index.

### Example: `array_set.c`
```c
c2wasm_js_var my_list = c2wasm_create_array();
c2wasm_js_var created_callback = c2wasm_create_function(my_func);
c2wasm_set_array_any_by_index(my_list, 0, created_callback);
c2wasm_set_array_bool_by_index(my_list, 1, 1);
c2wasm_set_array_double_by_index(my_list, 2, 3.14);
c2wasm_set_array_string_by_index(my_list, 3, "hello str setted");
c2wasm_set_array_long_by_index(my_list, 4, 123456789);
```

#### Supported Functions
- `c2wasm_set_array_any_by_index(array, index, value);`
- `c2wasm_set_array_bool_by_index(array, index, bool_value);`
- `c2wasm_set_array_double_by_index(array, index, double_value);`
- `c2wasm_set_array_string_by_index(array, index, string_value);`
- `c2wasm_set_array_long_by_index(array, index, long_value);`

#### Notes
- If the index is beyond the current array length, intermediate elements may be undefined.
- Overwrites any value at the target index.

---

## Appending Elements to an Array
To add elements to the end of an array, use the `c2wasm_append_array_<type>` functions. These automatically increase the array's length.

### Example: `array_append.c`
```c
c2wasm_js_var my_list = c2wasm_create_array();
c2wasm_js_var created_callback = c2wasm_create_function(my_func);
c2wasm_append_array_any(my_list, created_callback);
c2wasm_append_array_bool(my_list, 1);
c2wasm_append_array_double(my_list, 3.14);
c2wasm_append_array_string(my_list, "hello");
c2wasm_append_array_long(my_list, 123456789);
```

#### Supported Functions
- `c2wasm_append_array_any(array, value);`
- `c2wasm_append_array_bool(array, bool_value);`
- `c2wasm_append_array_double(array, double_value);`
- `c2wasm_append_array_string(array, string_value);`
- `c2wasm_append_array_long(array, long_value);`

#### Notes
- Appends to the end; does not overwrite existing elements.

---

## Practical Example: Assigning Array to an Object Property
You may want to assign the created array to a property of a JavaScript object, such as `window`:
```c
c2wasm_set_object_prop_any(c2wasm_window, "created_array", my_list);
```

---

## Comparison: Set by Index vs Append
| Operation           | Function Prefix         | Overwrites? | Use Case                                 |
|---------------------|------------------------|-------------|------------------------------------------|
| Set by Index        | `c2wasm_set_array_*_by_index` | Yes         | Update or insert at a specific position  |
| Append              | `c2wasm_append_array_*`       | No          | Add new elements to the end of the array |

---

## Best Practices & Tips
- Use `set by index` when you need to update or insert at a known position.
- Use `append` for growing arrays sequentially.
- Always ensure the array is created before setting or appending.
- When setting by index beyond the current size, be aware of potential gaps.

---

## Full Example
```c
#include "c2wasm.c"
#include <stdio.h>

c2wasm_js_var my_func() {
  printf("Hello from C!\n");
  return 0;
}

int main() {
  c2wasm_start();
  c2wasm_js_var my_list = c2wasm_create_array();
  c2wasm_js_var created_callback = c2wasm_create_function(my_func);
  c2wasm_set_array_any_by_index(my_list, 0, created_callback);
  c2wasm_set_array_bool_by_index(my_list, 1, 1);
  c2wasm_set_array_double_by_index(my_list, 2, 3.14);
  c2wasm_set_array_string_by_index(my_list, 3, "hello str setted");
  c2wasm_set_array_long_by_index(my_list, 4, 123456789);

  // Alternatively, appending
  c2wasm_append_array_any(my_list, created_callback);
  c2wasm_append_array_bool(my_list, 1);
  c2wasm_append_array_double(my_list, 3.14);
  c2wasm_append_array_string(my_list, "hello");
  c2wasm_append_array_long(my_list, 123456789);

  // Assign array to JS object property
  c2wasm_set_object_prop_any(c2wasm_window, "created_array", my_list);
}
```

---

## Conclusion
Setting and appending array properties in C2Wasm is straightforward and flexible. Choose the method that best fits your use case, and refer to the examples above for guidance.
