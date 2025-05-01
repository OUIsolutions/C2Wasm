# Setting Object Properties in C2Wasm

This document provides a comprehensive guide to setting properties on JavaScript objects from C code using the C2Wasm library. It covers the available APIs, usage patterns, examples, and important edge cases.

---

## Overview

C2Wasm allows you to create and manipulate JavaScript objects directly from C. You can set properties of different types (number, string, boolean, null, undefined, function, and any JS value) using a set of dedicated functions. This enables seamless interop between C and JS for building rich web applications.

---

## API Reference

### 1. Setting Properties by Type

- **Long Integer:**
  ```c
  void c2wasm_set_object_prop_long(c2wasm_js_var object, const char *prop_name, long value);
  ```
- **Double:**
  ```c
  void c2wasm_set_object_prop_double(c2wasm_js_var object, const char *prop_name, double value);
  ```
- **String:**
  ```c
  void c2wasm_set_object_prop_string(c2wasm_js_var object, const char *prop_name, const char *value);
  ```
- **Boolean:**
  ```c
  void c2wasm_set_object_prop_bool(c2wasm_js_var object, const char *prop_name, int value); // 0 = false, nonzero = true
  ```
- **Null:**
  ```c
  void c2wasm_set_object_prop_null(c2wasm_js_var object, const char *prop_name);
  ```
- **Undefined:**
  ```c
  void c2wasm_set_object_prop_undefined(c2wasm_js_var object, const char *prop_name);
  ```
- **Any JS Value:**
  ```c
  void c2wasm_set_object_prop_any(c2wasm_js_var object, const char *prop_name, c2wasm_js_var value);
  ```

### 2. Setting Function Properties

- **Function without internal args:**
  ```c
  void c2wasm_set_object_prop_function(c2wasm_js_var object, const char *prop_name, c2wasm_js_var (*callback)());
  ```
- **Function with internal args:**
  ```c
  void c2wasm_set_object_prop_function_with_internal_args(c2wasm_js_var object, const char *prop_name, c2wasm_js_var internal_args, c2wasm_js_var (*callback)(c2wasm_js_var internal_args));
  ```

---

## Usage Examples

### Example 1: Setting All Property Types
```c
#include "c2wasm.c"
#include <stdio.h>

c2wasm_js_var my_func_raw() {
  printf("my func raw called\n");
  return c2wasm_undefined;
}

c2wasm_js_var my_func_with_internal_args_raw(c2wasm_js_var internal_args) {
  double test_double = c2wasm_get_object_prop_double(internal_args, "test_double");
  printf("my func with internal args called\n");
  printf("test_double: %f\n", test_double);
  return c2wasm_undefined;
}

int main() {
  c2wasm_start();
  c2wasm_js_var self = c2wasm_create_object();
  c2wasm_set_object_prop_long(self, "test", 100);
  c2wasm_set_object_prop_double(self, "test_double", 110.0);
  c2wasm_set_object_prop_string(self, "test_string", "test");
  c2wasm_set_object_prop_bool(self, "test_bool", 1);
  c2wasm_set_object_prop_null(self, "test_null");
  c2wasm_set_object_prop_undefined(self, "test_undefined");
  c2wasm_js_var aray = c2wasm_create_array();
  c2wasm_set_object_prop_any(self, "test_array", aray);
  c2wasm_set_object_prop_function(self, "my_func", my_func_raw);
  c2wasm_set_object_prop_function_with_internal_args(self, "my_func_with_internal_args", self, my_func_with_internal_args_raw);
  c2wasm_set_object_prop_any(c2wasm_window, "created_obj", self);
}
```

### Example 2: Using `c2wasm_set_object_prop_any`
```c
#include "c2wasm.c"
#include <stdio.h>

int main() {
  c2wasm_start();
  c2wasm_js_var self = c2wasm_create_object();
  c2wasm_js_var test = c2wasm_create_long(10);
  c2wasm_set_object_prop_any(self, "test", test);
  c2wasm_js_var test_double = c2wasm_create_double(11.0);
  c2wasm_set_object_prop_any(self, "test_double", test_double);
  c2wasm_js_var test_string = c2wasm_create_string("test");
  c2wasm_set_object_prop_any(self, "test_string", test_string);
  c2wasm_js_var test_bool = c2wasm_create_bool(1);
  c2wasm_set_object_prop_any(self, "test_bool", test_bool);
  c2wasm_set_object_prop_any(self, "test_null", c2wasm_null);
  c2wasm_js_var aray = c2wasm_create_array();
  c2wasm_set_object_prop_any(self, "test_array", aray);
  c2wasm_set_object_prop_any(c2wasm_window, "obj_any", self);
}
```

### Example 3: Setting Function Properties as Any
```c
c2wasm_js_var my_func = c2wasm_create_function(my_func_raw);
c2wasm_set_object_prop_any(self, "my_func", my_func);

c2wasm_js_var my_func_with_internal_args = c2wasm_create_function_with_internal_args(self, my_func_with_internal_args_raw);
c2wasm_set_object_prop_any(self, "my_func_with_internal_args", my_func_with_internal_args);
```

---

## When to Use Each Setter

- Use the type-specific setters (`_long`, `_double`, `_string`, `_bool`, etc.) when you know the type at compile time.
- Use `c2wasm_set_object_prop_any` for dynamic or already-wrapped JS values, including objects, arrays, functions, or when transferring values between JS and C.
- Use the function setters to expose C callbacks as JS methods.

---

## Edge Cases & Tips

- **Overwriting:** Setting a property will overwrite any existing value at that property name.
- **Type Safety:** Type-specific setters will convert the C type to the corresponding JS type. Using the wrong setter may lead to unexpected JS values.
- **Null & Undefined:** `c2wasm_set_object_prop_null` and `c2wasm_set_object_prop_undefined` assign the proper JS values (`null` and `undefined`).
- **Functions:** When setting a function property, you can pass either a C function pointer or a wrapped JS function (via `c2wasm_create_function`).
- **Window/Object Properties:** You can set properties on global objects like `window` using `c2wasm_window`.
- **Arrays as Properties:** You can assign arrays to object properties using `c2wasm_set_object_prop_any`.
- **Memory Management:** If you create intermediate JS values (objects, arrays, functions), ensure you manage their lifetimes appropriately if your application is long-running.

---

## Full Example: Creating and Exposing an Object
```c
#include "c2wasm.c"
#include <stdio.h>

int main() {
  c2wasm_start();
  c2wasm_js_var obj = c2wasm_create_object();
  c2wasm_set_object_prop_long(obj, "counter", 42);
  c2wasm_set_object_prop_string(obj, "description", "A C-created object");
  c2wasm_set_object_prop_bool(obj, "active", 1);
  c2wasm_set_object_prop_null(obj, "maybe_null");
  c2wasm_set_object_prop_undefined(obj, "maybe_undefined");
  c2wasm_set_object_prop_any(c2wasm_window, "my_c_object", obj);
}
```

---

## Best Practices

- Prefer type-specific setters for clarity and safety.
- Use `c2wasm_set_object_prop_any` for maximum flexibility.
- Always check for errors in your C code when interacting with JS (e.g., null pointers, invalid property names).
- Document your C functions exposed to JS for consumers.

---

## See Also
- [Getting Object Properties](./getting_object_props.md)
- [Setting Array Properties](./setting_array_props.md)
- [C2Wasm Examples Directory](../examples/)

---

By following these patterns, you can robustly set and manage JS object properties from C using C2Wasm, enabling powerful WebAssembly applications with rich JS interop.
