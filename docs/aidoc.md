# C2Wasm AI-Optimized API Reference

## Core Initialization
```c
c2wasm_start() // MANDATORY: Call before any C2Wasm operations
```

## Type Constants
```c
C2WASM_UNDEFINED_TYPE = 0
C2WASM_NULL_TYPE = 1
C2WASM_BOOLEAN_TYPE = 2
C2WASM_NUMBER_TYPE = 3
C2WASM_STRING_TYPE = 4
C2WASM_FUNCTION_TYPE = 5
C2WASM_OBJECT_TYPE = 6
C2WASM_ARRAY_TYPE = 7
```

## Global Variables
```c
c2wasm_window    // JavaScript window object
c2wasm_document  // JavaScript document object
c2wasm_arguments // Function arguments array (only valid inside functions)
c2wasm_undefined // JavaScript undefined value
c2wasm_null      // JavaScript null value
```

## Object Creation
```c
c2wasm_js_var c2wasm_create_object()
c2wasm_js_var c2wasm_create_array()
c2wasm_js_var c2wasm_create_string(const char* str)
c2wasm_js_var c2wasm_create_long(long value)
c2wasm_js_var c2wasm_create_double(double value)
c2wasm_js_var c2wasm_create_bool(int value)
c2wasm_js_var c2wasm_create_function(c2wasm_js_var (*func)())
c2wasm_js_var c2wasm_create_function_with_internal_args(c2wasm_js_var internal_args, c2wasm_js_var (*func)(c2wasm_js_var))
```

## Object Property Setters
```c
// Generic setter
void c2wasm_set_object_prop_any(c2wasm_js_var obj, const char* prop_name, c2wasm_js_var value)

// Type-specific setters
void c2wasm_set_object_prop_string(c2wasm_js_var obj, const char* prop_name, const char* value)
void c2wasm_set_object_prop_long(c2wasm_js_var obj, const char* prop_name, long value)
void c2wasm_set_object_prop_double(c2wasm_js_var obj, const char* prop_name, double value)
void c2wasm_set_object_prop_bool(c2wasm_js_var obj, const char* prop_name, int value)
void c2wasm_set_object_prop_null(c2wasm_js_var obj, const char* prop_name)
void c2wasm_set_object_prop_undefined(c2wasm_js_var obj, const char* prop_name)
void c2wasm_set_object_prop_function(c2wasm_js_var obj, const char* prop_name, c2wasm_js_var (*func)())
void c2wasm_set_object_prop_function_with_internal_args(c2wasm_js_var obj, const char* prop_name, c2wasm_js_var internal_args, c2wasm_js_var (*func)(c2wasm_js_var))
```

## Object Property Getters
```c
// Type checker
int c2wasm_get_object_prop_type(c2wasm_js_var obj, const char* prop_name)

// Generic getter
c2wasm_js_var c2wasm_get_object_prop_any(c2wasm_js_var obj, const char* prop_name)

// Type-specific getters
double c2wasm_get_object_prop_double(c2wasm_js_var obj, const char* prop_name)
long c2wasm_get_object_prop_long(c2wasm_js_var obj, const char* prop_name)
int c2wasm_get_object_prop_bool(c2wasm_js_var obj, const char* prop_name)

// String operations
int c2wasm_get_object_string_len_prop(c2wasm_js_var obj, const char* prop_name)
void c2wams_object_memcpy_string(c2wasm_js_var obj, const char* prop_name, char* buffer, int size)
```

## Array Operations - Setters
```c
// By index setters
void c2wasm_set_array_any_by_index(c2wasm_js_var arr, int index, c2wasm_js_var value)
void c2wasm_set_array_string_by_index(c2wasm_js_var arr, int index, const char* value)
void c2wasm_set_array_long_by_index(c2wasm_js_var arr, int index, long value)
void c2wasm_set_array_double_by_index(c2wasm_js_var arr, int index, double value)
void c2wasm_set_array_bool_by_index(c2wasm_js_var arr, int index, int value)

// Append operations
void c2wasm_append_array_any(c2wasm_js_var arr, c2wasm_js_var value)
void c2wasm_append_array_string(c2wasm_js_var arr, const char* value)
void c2wasm_append_array_long(c2wasm_js_var arr, long value)
void c2wasm_append_array_double(c2wasm_js_var arr, double value)
void c2wasm_append_array_bool(c2wasm_js_var arr, int value)
```

## Array Operations - Getters
```c
// Size and type
long c2wasm_get_array_size(c2wasm_js_var arr)
int c2wasm_get_array_type_by_index(c2wasm_js_var arr, int index)

// Generic getter
c2wasm_js_var c2wasm_get_array_any_by_index(c2wasm_js_var arr, int index)

// Type-specific getters
double c2wasm_get_array_double_by_index(c2wasm_js_var arr, int index, void* unused, int unused2)
long c2wasm_get_array_long_by_index(c2wasm_js_var arr, int index)

// String operations
int c2wasm_get_array_string_size_by_index(c2wasm_js_var arr, int index)
void c2wasm_array_memcpy_string(c2wasm_js_var arr, int index, int start_pos, char* buffer, int size)
```

## String Operations
```c
long c2wasm_get_string_len(c2wasm_js_var str)
void c2wasm_memcpy_string(c2wasm_js_var str, int start_pos, char* buffer, int size)
```

## Function Calls
```c
c2wasm_js_var c2wasm_call_object_prop(c2wasm_js_var obj, const char* method_name, c2wasm_js_var args_array)
```

## Function Pattern Examples

### Basic Function
```c
c2wasm_js_var function_name() {
    // Access arguments via c2wasm_arguments
    // Return c2wasm_undefined or other value
    return c2wasm_undefined;
}
```

### Function with Internal Args
```c
c2wasm_js_var function_name(c2wasm_js_var internal_args) {
    // internal_args is passed when creating function
    return c2wasm_undefined;
}
```

## Common Patterns

### DOM Manipulation
```c
c2wasm_js_var args = c2wasm_create_array();
c2wasm_append_array_string(args, "element_id");
c2wasm_js_var element = c2wasm_call_object_prop(c2wasm_document, "getElementById", args);
c2wasm_set_object_prop_string(element, "innerHTML", "content");
```

### Error Creation
```c
c2wasm_js_var error_args = c2wasm_create_array();
c2wasm_append_array_string(error_args, "Error message");
return c2wasm_call_object_prop(c2wasm_window, "Error", error_args);
```

### Object Keys Iteration
```c
c2wasm_js_var Object = c2wasm_get_object_prop_any(c2wasm_window, "Object");
c2wasm_js_var keys_args = c2wasm_create_array();
c2wasm_append_array_any(keys_args, target_object);
c2wasm_js_var keys = c2wasm_call_object_prop(Object, "keys", keys_args);
```

## Memory Management Rules
- All c2wasm_js_var are JavaScript references
- No manual memory management needed for JS objects
- Use malloc/free only for C buffers
- String buffers must be null-terminated manually

## Type Checking Pattern
```c
if(c2wasm_get_array_type_by_index(arr, index) == C2WASM_STRING_TYPE) {
    // Handle string
}
```

## String Extraction Pattern
```c
int size = c2wasm_get_array_string_size_by_index(arr, index);
char buffer[size + 1];
c2wasm_array_memcpy_string(arr, index, 0, buffer, size);