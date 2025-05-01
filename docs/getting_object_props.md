# Getting Object Properties in C2Wasm

This guide explains how to retrieve and iterate over properties of JavaScript objects from C code using the C2Wasm framework, based on the example from `examples/object_iteration/object_iteration.c`.

## Table of Contents
1. [Introduction](#introduction)
2. [Step-by-Step Example](#step-by-step-example)
3. [API Reference](#c2wasm-object-property-api-reference)
4. [Best Practices](#best-practices-and-tips)
5. [See Also](#see-also)

## Introduction

C2Wasm enables C code to access JavaScript object properties when compiled to WebAssembly. This document covers how to safely retrieve object properties, determine their types, and access their values in a type-safe manner.

---

## Step-by-Step Example

Below is an example function that retrieves and processes object properties:

```c
c2wasm_js_var print_elements_of_object() {
    // Check if first argument is an object
    if (c2wasm_get_array_type_by_index(c2wasm_arguments, 0) != C2WASM_OBJECT_TYPE) {
        c2wasm_js_var error_args = c2wasm_create_array();
        c2wasm_append_array_string(error_args, "Error: first argument must be an object");
        return c2wasm_call_object_prop(c2wasm_window, "Error", error_args);
    }
    
    // Get the object
    c2wasm_js_var current_object = c2wasm_get_array_any_by_index(c2wasm_arguments, 0);
    
    // Get Object.keys()
    c2wasm_js_var Object = c2wasm_get_object_prop_any(c2wasm_window, "Object");
    c2wasm_js_var keys_args = c2wasm_create_array();
    c2wasm_append_array_any(keys_args, current_object);
    c2wasm_js_var keys = c2wasm_call_object_prop(Object, "keys", keys_args);
    
    // Iterate through all properties
    long size = c2wasm_get_array_size(keys);
    for (int i = 0; i < size; i++) {
        // Get the key name
        int key_size = c2wasm_get_array_string_size_by_index(keys, i);
        char buffer_key[key_size + 1];
        c2wasm_array_memcpy_string(keys, i, 0, buffer_key, key_size);
        buffer_key[key_size] = '\0';
        
        // Get the property value type
        int value_type = c2wasm_get_object_prop_type(current_object, buffer_key);
        
        // Handle different types
        if (value_type == C2WASM_STRING_TYPE) {
            int value_size = c2wasm_get_object_string_len_prop(current_object, buffer_key);
            char buffer_value[value_size + 1];
            c2wams_object_memcpy_string(current_object, buffer_key, buffer_value, value_size);
            buffer_value[value_size] = '\0';
            printf("%s: %s\n", buffer_key, buffer_value);
        }
        if (value_type == C2WASM_NUMBER_TYPE) {
            double value = c2wasm_get_object_prop_double(current_object, buffer_key);
            printf("%s: %f\n", buffer_key, value);
        }
        if (value_type == C2WASM_BOOLEAN_TYPE) {
            int value = c2wasm_get_object_prop_bool(current_object, buffer_key);
            printf("%s: %s\n", buffer_key, value ? "true" : "false");
        }
        if (value_type == C2WASM_NULL_TYPE) {
            printf("%s: null\n", buffer_key);
        }
        if (value_type == C2WASM_UNDEFINED_TYPE) {
            printf("%s: undefined\n", buffer_key);
        }
    }
    return c2wasm_undefined;
}
```

### Key Processing Steps

1. **Type Checking**: Ensure the input is an object
2. **Object Access**: Get the object from arguments
3. **Property Enumeration**: Use Object.keys() to get all property names
4. **Iteration**: Loop through each property name
5. **Type Detection**: Check the type of each property value
6. **Type-Specific Handling**: Process each property according to its type

---

## C2Wasm Object Property API Reference

| Function | Description |
|----------|-------------|
| `c2wasm_get_object_prop_type(object, prop_name)` | Returns the type of the specified property |
| `c2wasm_get_object_prop_any(object, prop_name)` | Retrieves a property as a generic JS variable |
| `c2wasm_get_object_string_len_prop(object, prop_name)` | Returns the length of a string property |
| `c2wams_object_memcpy_string(object, prop_name, buffer, length)` | Copies a string property into a C buffer |
| `c2wasm_get_object_prop_double(object, prop_name)` | Retrieves a number property as a double |
| `c2wasm_get_object_prop_bool(object, prop_name)` | Retrieves a boolean property as an int (0 or 1) |

### Working with Object.keys()

```c
// Get the Object constructor
c2wasm_js_var Object = c2wasm_get_object_prop_any(c2wasm_window, "Object");

// Create args array with the object
c2wasm_js_var keys_args = c2wasm_create_array();
c2wasm_append_array_any(keys_args, obj);

// Call Object.keys() to get property names
c2wasm_js_var keys = c2wasm_call_object_prop(Object, "keys", keys_args);
```

### Type Constants

Same type constants as used for arrays:

| Constant | Description |
|----------|-------------|
| `C2WASM_STRING_TYPE` | Property is a string |
| `C2WASM_NUMBER_TYPE` | Property is a number |
| `C2WASM_BOOLEAN_TYPE` | Property is a boolean |
| `C2WASM_NULL_TYPE` | Property is null |
| `C2WASM_UNDEFINED_TYPE` | Property is undefined |
| `C2WASM_ARRAY_TYPE` | Property is an array |
| `C2WASM_OBJECT_TYPE` | Property is an object |

---

## Best Practices and Tips

- **Type Safety**: Always check property types before accessing values
- **Buffer Management**: For string properties, ensure buffers are properly sized and null-terminated
- **Property Names**: Use Object.keys() to enumerate properties dynamically
- **Error Handling**: Validate inputs and return informative errors
- **Nested Objects**: For recursive property access, implement depth-limited recursion
- **Performance**: Consider caching key lists when iterating multiple times
- **Memory Management**: Be careful with buffer allocation for large objects

## See Also

- [Setting Object Properties](./setting_object_props.md)
- [Getting Array Properties](./getting_array_props.md)
- [Setting Array Properties](./setting_array_props.md)

Accessing object properties in C2Wasm involves:
- Validating input types
- Retrieving keys with `Object.keys`
- Iterating and type-checking each property
- Using the appropriate API to extract and process each value

This approach allows robust and type-safe interaction with dynamic JS objects from C code, enabling advanced interoperability in your C2Wasm projects.

For more examples, see `examples/object_iteration/object_iteration.c` and related documentation.