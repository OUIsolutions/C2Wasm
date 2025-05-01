# Getting Object Properties in C2Wasm

This guide provides a comprehensive walkthrough for **retrieving and iterating over properties of JavaScript objects from C code using the C2Wasm framework**. We will use the example from `examples/object_iteration/object_iteration.c` to illustrate each step in detail.

---

## Table of Contents
1. [Introduction](#introduction)
2. [Prerequisites](#prerequisites)
3. [Overview of the Example](#overview-of-the-example)
4. [Step-by-Step Walkthrough](#step-by-step-walkthrough)
    - [Type Checking](#type-checking)
    - [Retrieving the Object](#retrieving-the-object)
    - [Getting the Keys](#getting-the-keys)
    - [Iterating Over Object Properties](#iterating-over-object-properties)
    - [Accessing Property Values](#accessing-property-values)
    - [Handling Different Value Types](#handling-different-value-types)
    - [Error Handling](#error-handling)
5. [Complete Example](#complete-example)
6. [Edge Cases and Tips](#edge-cases-and-tips)
7. [Summary](#summary)

---

## Introduction

C2Wasm is a framework that allows calling C functions from JavaScript and vice versa, enabling seamless interaction between C and JS objects. A common task is to **access and iterate over the properties of a JavaScript object** from C code. This is essential for applications that need to process dynamic data structures, such as configuration objects, user data, or any object passed from JS to C.

---

## Prerequisites
- **C2Wasm installed and set up** in your project.
- Familiarity with basic C programming.
- Basic understanding of JavaScript objects.

---

## Overview of the Example

The function `print_elements_of_object` in `object_iteration.c` demonstrates how to receive a JS object as an argument and print all its properties and values, handling all major JS types.

---

## Step-by-Step Walkthrough

### 1. Type Checking
Before accessing properties, ensure the argument is an object:
```c
if (c2wasm_get_array_type_by_index(c2wasm_arguments, 0) != C2WASM_OBJECT_TYPE) {
    // Handle error
}
```
- **Purpose:** Prevents errors by ensuring you only process objects.
- **What happens:** If the argument is not an object, an error is returned to JS.

> **Note:** This document only covers property access for JavaScript objects. For working with arrays, see the dedicated array documentation.

### 2. Retrieving the Object
```c
c2wasm_js_var current_object = c2wasm_get_array_any_by_index(c2wasm_arguments, 0);
```
- **Purpose:** Extracts the JS object from the arguments array.

### 3. Getting the Keys
```c
c2wasm_js_var Object = c2wasm_get_object_prop_any(c2wasm_window, "Object");
c2wasm_js_var keys_args = c2wasm_create_array();
c2wasm_append_array_any(keys_args, current_object);
c2wasm_js_var keys = c2wasm_call_object_prop(Object, "keys", keys_args);
```
- **Purpose:** Calls `Object.keys(obj)` in JS to get an array of property names (not array indices).
- **How:**
    - Retrieves the global `Object`.
    - Prepares arguments for `Object.keys`.
    - Calls `Object.keys` and stores the result in `keys`.

### 4. Iterating Over Object Properties
```c
long size = c2wasm_get_array_size(keys);
for (int i = 0; i < size; i++) {
    // ...
}
```
- **Purpose:** Loops through each property name (key) in the object (not array indices).

### 5. Accessing Property Values
For each key:
```c
int key_size = c2wasm_get_array_string_size_by_index(keys, i);
char buffer_key[key_size + 1];
c2wasm_array_memcpy_string(keys, i, 0, buffer_key, key_size);
buffer_key[key_size] = '\0';
int value_type = c2wasm_get_object_prop_type(current_object, buffer_key);
```
- **Purpose:**
    - Retrieves the property name as a string.
    - Determines the type of the property value.

### 6. Handling Different Value Types
Depending on `value_type`, use the corresponding C2Wasm API to retrieve and print the value:
- **String:**
    ```c
    int value_size = c2wasm_get_object_string_len_prop(current_object, buffer_key);
    char buffer_value[value_size + 1];
    c2wams_object_memcpy_string(current_object, buffer_key, buffer_value, value_size);
    buffer_value[value_size] = '\0';
    printf("%s: %s\n", buffer_key, buffer_value);
    ```
- **Number:**
    ```c
    double value = c2wasm_get_object_prop_double(current_object, buffer_key);
    printf("%s: %f\n", buffer_key, value);
    ```
- **Boolean:**
    ```c
    int value = c2wasm_get_object_prop_bool(current_object, buffer_key);
    printf("%s: %s\n", buffer_key, value ? "true" : "false");
    ```
- **Null:**
    ```c
    printf("%s: null\n", buffer_key);
    ```
- **Undefined:**
    ```c
    printf("%s: undefined\n", buffer_key);
    ```

### 7. Error Handling
If the argument is not an object:
```c
c2wasm_js_var error_args = c2wasm_create_array();
c2wasm_append_array_string(error_args, "Error: first argument must be an object");
return c2wasm_call_object_prop(c2wasm_window, "Error", error_args);
```
- **Purpose:** Returns an error to JS, following C2Wasm conventions.

---

## Complete Example
Here is the relevant function from `object_iteration.c`:
```c
// Receives a JS object and prints all properties and values
c2wasm_js_var print_elements_of_object() {
    if (c2wasm_get_array_type_by_index(c2wasm_arguments, 0) != C2WASM_OBJECT_TYPE) {
        c2wasm_js_var error_args = c2wasm_create_array();
        c2wasm_append_array_string(error_args, "Error: first argument must be an object");
        return c2wasm_call_object_prop(c2wasm_window, "Error", error_args);
    }
    c2wasm_js_var current_object = c2wasm_get_array_any_by_index(c2wasm_arguments, 0);
    c2wasm_js_var Object = c2wasm_get_object_prop_any(c2wasm_window, "Object");
    c2wasm_js_var keys_args = c2wasm_create_array();
    c2wasm_append_array_any(keys_args, current_object);
    c2wasm_js_var keys = c2wasm_call_object_prop(Object, "keys", keys_args);
    long size = c2wasm_get_array_size(keys);
    for (int i = 0; i < size; i++) {
        int key_size = c2wasm_get_array_string_size_by_index(keys, i);
        char buffer_key[key_size + 1];
        c2wasm_array_memcpy_string(keys, i, 0, buffer_key, key_size);
        buffer_key[key_size] = '\0';
        int value_type = c2wasm_get_object_prop_type(current_object, buffer_key);
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

---

## Edge Cases and Tips
- **Non-Object Arguments:** Always check the type before accessing properties.
- **Nested Objects:** This example does not recursively print nested objects. Add recursion if needed.
- **Performance:** For large objects, consider optimizing string buffer allocation.
- **Unicode:** Ensure buffer sizes account for multi-byte characters if your objects use Unicode property names or values.
- **Arrays:** This document does not cover array property access or iteration. For array-specific operations, see the corresponding documentation.
- **API Reference:**
    - `c2wasm_get_object_prop_type`, `c2wasm_get_object_string_len_prop`, `c2wasm_get_object_prop_double`, etc., are C2Wasm API calls for type-safe property access.

---

## Summary

Accessing object properties in C2Wasm involves:
- Validating input types
- Retrieving keys with `Object.keys`
- Iterating and type-checking each property
- Using the appropriate API to extract and process each value

This approach allows robust and type-safe interaction with dynamic JS objects from C code, enabling advanced interoperability in your C2Wasm projects.

For more examples, see `examples/object_iteration/object_iteration.c` and related documentation.