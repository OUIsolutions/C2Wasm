# Setting Object Properties in C2Wasm

This guide explains how to set properties on JavaScript objects from C code using the C2Wasm framework, based on examples from `examples/object_properties`.

## Table of Contents
1. [Introduction](#introduction)
2. [Creating Objects](#creating-objects)
3. [Setting Properties](#setting-properties-by-type)
4. [Function Properties](#setting-function-properties)
5. [API Reference](#c2wasm-object-property-api-reference)
6. [Best Practices](#best-practices)
7. [See Also](#see-also)

## Introduction

C2Wasm enables C code to create and manipulate JavaScript objects when compiled to WebAssembly. This document covers how to create objects and set properties of different types, including numbers, strings, booleans, null, undefined, functions, and other JavaScript values.

---

## Creating Objects

To create a new JavaScript object, use the `c2wasm_create_object()` function:

```c
c2wasm_js_var my_obj = c2wasm_create_object();
```

This creates an empty JavaScript object that you can then populate with properties.

## Setting Properties by Type

C2Wasm provides type-specific functions for setting object properties:

```c
// Create an object
c2wasm_js_var obj = c2wasm_create_object();

// Set various types of properties
c2wasm_set_object_prop_long(obj, "count", 100);
c2wasm_set_object_prop_double(obj, "price", 99.99);
c2wasm_set_object_prop_string(obj, "name", "Product");
c2wasm_set_object_prop_bool(obj, "available", 1);  // true
c2wasm_set_object_prop_null(obj, "metadata");
c2wasm_set_object_prop_undefined(obj, "optional");

// Set a property with a nested array
c2wasm_js_var array = c2wasm_create_array();
c2wasm_append_array_string(array, "item1");
c2wasm_append_array_string(array, "item2");
c2wasm_set_object_prop_any(obj, "items", array);
```

### Available Property Setter Functions

| Function | Description |
|----------|-------------|
| `c2wasm_set_object_prop_long(obj, name, value)` | Sets an integer property |
| `c2wasm_set_object_prop_double(obj, name, value)` | Sets a floating-point property |
| `c2wasm_set_object_prop_string(obj, name, value)` | Sets a string property |
| `c2wasm_set_object_prop_bool(obj, name, value)` | Sets a boolean property (0 = false, non-zero = true) |
| `c2wasm_set_object_prop_null(obj, name)` | Sets a property to JavaScript `null` |
| `c2wasm_set_object_prop_undefined(obj, name)` | Sets a property to JavaScript `undefined` |
| `c2wasm_set_object_prop_any(obj, name, value)` | Sets a property to any JavaScript value |

---

## Setting Function Properties

C2Wasm allows you to set object properties that are callable JavaScript functions:

```c
// Function with no internal state
c2wasm_js_var my_func() {
  printf("Function called!\n");
  return c2wasm_undefined;
}

// Function with access to internal state
c2wasm_js_var my_stateful_func(c2wasm_js_var internal_args) {
  double value = c2wasm_get_object_prop_double(internal_args, "counter");
  printf("Counter value: %f\n", value);
  return c2wasm_undefined;
}

// Later in your code:
c2wasm_js_var obj = c2wasm_create_object();

// Set a simple function property
c2wasm_set_object_prop_function(obj, "simpleMethod", my_func);

// Create some internal state
c2wasm_js_var state = c2wasm_create_object();
c2wasm_set_object_prop_double(state, "counter", 42.0);

// Set a function with access to internal state
c2wasm_set_object_prop_function_with_internal_args(
    obj, "statefulMethod", state, my_stateful_func);
```

### Alternative Method Using Any Type

You can also create functions first and then set them as properties:

```c
// Create the functions
c2wasm_js_var func1 = c2wasm_create_function(my_func);
c2wasm_js_var func2 = c2wasm_create_function_with_internal_args(state, my_stateful_func);

// Set them as properties
c2wasm_set_object_prop_any(obj, "method1", func1);
c2wasm_set_object_prop_any(obj, "method2", func2);
```

## C2Wasm Object Property API Reference

### Object Creation

| Function | Description |
|----------|-------------|
| `c2wasm_create_object()` | Creates a new empty JavaScript object |

### Property Setters

| Function | Description |
|----------|-------------|
| `c2wasm_set_object_prop_long(obj, name, value)` | Sets an integer property |
| `c2wasm_set_object_prop_double(obj, name, value)` | Sets a floating-point property |
| `c2wasm_set_object_prop_string(obj, name, value)` | Sets a string property |
| `c2wasm_set_object_prop_bool(obj, name, value)` | Sets a boolean property |
| `c2wasm_set_object_prop_null(obj, name)` | Sets a property to null |
| `c2wasm_set_object_prop_undefined(obj, name)` | Sets a property to undefined |
| `c2wasm_set_object_prop_any(obj, name, value)` | Sets a property to any JavaScript value |

### Function Property Setters

| Function | Description |
|----------|-------------|
| `c2wasm_set_object_prop_function(obj, name, callback)` | Sets a function property without state |
| `c2wasm_set_object_prop_function_with_internal_args(obj, name, internal_args, callback)` | Sets a function property with state |
| `c2wasm_create_function(callback)` | Creates a function to be set via `set_object_prop_any` |
| `c2wasm_create_function_with_internal_args(internal_args, callback)` | Creates a stateful function |

## Complete Example

```c
#include "c2wasm.c"
#include <stdio.h>

// Simple callback function
c2wasm_js_var my_callback() {
  printf("Callback function executed!\n");
  return c2wasm_undefined;
}

// Function with internal state
c2wasm_js_var stateful_callback(c2wasm_js_var state) {
  double counter = c2wasm_get_object_prop_double(state, "counter");
  printf("Counter value: %f\n", counter);
  
  // Increment the counter
  counter += 1.0;
  c2wasm_set_object_prop_double(state, "counter", counter);
  
  return c2wasm_undefined;
}

int main() {
  c2wasm_start();
  
  // Create main object
  c2wasm_js_var obj = c2wasm_create_object();
  
  // Set primitive properties
  c2wasm_set_object_prop_long(obj, "id", 42);
  c2wasm_set_object_prop_string(obj, "name", "C2Wasm Object");
  c2wasm_set_object_prop_bool(obj, "enabled", 1);
  c2wasm_set_object_prop_null(obj, "nullProp");
  c2wasm_set_object_prop_undefined(obj, "undefinedProp");
  
  // Create nested array
  c2wasm_js_var tags = c2wasm_create_array();
  c2wasm_append_array_string(tags, "wasm");
  c2wasm_append_array_string(tags, "c");
  c2wasm_append_array_string(tags, "javascript");
  c2wasm_set_object_prop_any(obj, "tags", tags);
  
  // Set a simple function
  c2wasm_set_object_prop_function(obj, "simpleMethod", my_callback);
  
  // Set stateful function
  c2wasm_js_var state = c2wasm_create_object();
  c2wasm_set_object_prop_double(state, "counter", 0.0);
  c2wasm_set_object_prop_function_with_internal_args(
      obj, "countingMethod", state, stateful_callback);
  
  // Make object available to JavaScript
  c2wasm_set_object_prop_any(c2wasm_window, "cObject", obj);
  
  return 0;
}
```

## Best Practices

- **Type Specificity**: Use type-specific setters when possible for clarity and safety
- **Property Naming**: Follow JavaScript naming conventions for object properties
- **Function Scope**: Use internal args to maintain state across function calls
- **Object Hierarchies**: Build complex objects by nesting objects and arrays
- **Global Access**: Expose objects to JavaScript by setting them as properties of `c2wasm_window`
- **Overwriting**: Be aware that setting a property overwrites any previous value
- **Memory Management**: Create intermediate objects only when needed

## See Also

- [Getting Object Properties](./getting_object_props.md)
- [Getting Array Properties](./getting_array_props.md)
- [Setting Array Properties](./setting_array_props.md)
