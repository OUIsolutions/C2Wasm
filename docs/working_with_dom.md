# Working with the DOM in C2Wasm

This guide explains how to manipulate the Document Object Model (DOM) using the C2Wasm framework, allowing you to create dynamic web content directly from C code.

## Table of Contents
1. [Introduction](#introduction)
2. [Accessing DOM Elements](#accessing-dom-elements)
3. [Modifying DOM Elements](#modifying-dom-elements)
4. [Creating DOM Elements](#creating-dom-elements)
5. [Event Handling](#event-handling)
6. [DOM Traversal](#dom-traversal)
7. [Advanced DOM Manipulation](#advanced-dom-manipulation)
8. [Best Practices](#best-practices)
9. [Complete Examples](#complete-examples)
10. [See Also](#see-also)

## Introduction

C2Wasm provides a seamless interface between C code and the browser's DOM API. Using the DOM manipulation functions, you can:

- Access existing DOM elements
- Modify element properties, styles, and attributes
- Create and append new elements
- Handle DOM events
- Perform DOM traversal and searching

This document covers the core concepts and functions needed to effectively work with the DOM in your C2Wasm applications.

---

## Accessing DOM Elements

C2Wasm provides several built-in DOM globals for convenience:

```c
// Pre-defined DOM globals
c2wasm_window   // JavaScript window object
c2wasm_document // JavaScript document object
c2wasm_body     // document.body shorthand
```

### Selecting Elements

To select elements from the DOM, use these document methods:

```c
// Get element by ID
c2wasm_js_var element = c2wasm_call_object_prop_string(c2wasm_document, "getElementById", "my-element-id");

// Query selector (returns first matching element)
c2wasm_js_var element = c2wasm_call_object_prop_string(c2wasm_document, "querySelector", ".my-class");

// Query selector all (returns all matching elements)
c2wasm_js_var elements = c2wasm_call_object_prop_string(c2wasm_document, "querySelectorAll", "div.container");
```

### Checking if Element Exists

Always check if an element exists before attempting to manipulate it:

```c
c2wasm_js_var element = c2wasm_call_object_prop_string(c2wasm_document, "getElementById", "my-element-id");
if (element != c2wasm_null && element != c2wasm_undefined) {
    // Element exists, now it's safe to manipulate it
}
```

## Modifying DOM Elements

Once you have a reference to a DOM element, you can modify its content, attributes, and styles.

### Text Content

```c
// Set text content
c2wasm_set_object_prop_string(element, "textContent", "Hello from C2Wasm!");

// Get text content
int text_length = c2wasm_get_object_string_len_prop(element, "textContent");
char text_buffer[text_length + 1];
c2wams_object_memcpy_string(element, "textContent", text_buffer, text_length);
text_buffer[text_length] = '\0';
```

### HTML Content

```c
// Set inner HTML
c2wasm_set_object_prop_string(element, "innerHTML", "<strong>Bold text</strong> and <em>emphasized text</em>");
```

### Attributes

```c
// Set an attribute
c2wasm_js_var attrs_args = c2wasm_create_array();
c2wasm_append_array_string(attrs_args, "data-custom");
c2wasm_append_array_string(attrs_args, "custom-value");
c2wasm_call_object_prop(element, "setAttribute", attrs_args);

// Get an attribute
c2wasm_js_var get_attr_args = c2wasm_create_array();
c2wasm_append_array_string(get_attr_args, "data-custom");
c2wasm_js_var attr_value = c2wasm_call_object_prop(element, "getAttribute", get_attr_args);
```

### Styles

```c
// Access the style object
c2wasm_js_var style = c2wasm_get_object_prop_any(element, "style");

// Set style properties
c2wasm_set_object_prop_string(style, "color", "blue");
c2wasm_set_object_prop_string(style, "backgroundColor", "lightgray");
c2wasm_set_object_prop_string(style, "fontSize", "16px");

// Alternative inline approach
c2wasm_set_object_prop_string(element, "style", "color: blue; background-color: lightgray; font-size: 16px;");
```

### CSS Classes

```c
// Access the classList
c2wasm_js_var classList = c2wasm_get_object_prop_any(element, "classList");

// Add a class
c2wasm_js_var add_args = c2wasm_create_array();
c2wasm_append_array_string(add_args, "highlight");
c2wasm_call_object_prop(classList, "add", add_args);

// Remove a class
c2wasm_js_var remove_args = c2wasm_create_array();
c2wasm_append_array_string(remove_args, "disabled");
c2wasm_call_object_prop(classList, "remove", remove_args);

// Toggle a class
c2wasm_js_var toggle_args = c2wasm_create_array();
c2wasm_append_array_string(toggle_args, "active");
c2wasm_call_object_prop(classList, "toggle", toggle_args);

// Check if element has a class
c2wasm_js_var contains_args = c2wasm_create_array();
c2wasm_append_array_string(contains_args, "selected");
c2wasm_js_var has_class = c2wasm_call_object_prop(classList, "contains", contains_args);
```

## Creating DOM Elements

### Creating Elements

```c
// Create a new element
c2wasm_js_var create_args = c2wasm_create_array();
c2wasm_append_array_string(create_args, "div");
c2wasm_js_var new_element = c2wasm_call_object_prop(c2wasm_document, "createElement", create_args);

// Set properties
c2wasm_set_object_prop_string(new_element, "id", "new-element-id");
c2wasm_set_object_prop_string(new_element, "className", "new-element-class");
c2wasm_set_object_prop_string(new_element, "textContent", "This is a new element");
```

### Appending and Inserting Elements

```c
// Append to parent
c2wasm_js_var append_args = c2wasm_create_array();
c2wasm_append_array_any(append_args, new_element);
c2wasm_call_object_prop(c2wasm_body, "appendChild", append_args);

// Insert before another element
c2wasm_js_var reference_element = c2wasm_call_object_prop_string(c2wasm_document, "getElementById", "reference-id");
c2wasm_js_var insert_args = c2wasm_create_array();
c2wasm_append_array_any(insert_args, new_element);
c2wasm_append_array_any(insert_args, reference_element);
c2wasm_call_object_prop(c2wasm_body, "insertBefore", insert_args);
```

### Removing Elements

```c
// Remove an element
c2wasm_js_var remove_args = c2wasm_create_array();
c2wasm_call_object_prop(element, "remove", remove_args);

// Alternative: Remove a child from parent
c2wasm_js_var parent = c2wasm_get_object_prop_any(element, "parentNode");
c2wasm_js_var remove_child_args = c2wasm_create_array();
c2wasm_append_array_any(remove_child_args, element);
c2wasm_call_object_prop(parent, "removeChild", remove_child_args);
```

## Event Handling

### Adding Event Listeners

```c
// Event handler function
c2wasm_js_var click_handler(c2wasm_js_var event) {
    printf("Element was clicked!\n");
    
    // Get the target element
    c2wasm_js_var target = c2wasm_get_object_prop_any(event, "target");
    
    // Change something on the target
    c2wasm_set_object_prop_string(target, "textContent", "Clicked!");
    
    return c2wasm_undefined;
}

// Attach event listener
c2wasm_js_var handler = c2wasm_create_function(click_handler);
c2wasm_js_var listener_args = c2wasm_create_array();
c2wasm_append_array_string(listener_args, "click");
c2wasm_append_array_any(listener_args, handler);
c2wasm_call_object_prop(element, "addEventListener", listener_args);
```

### Event Handler with State

```c
c2wasm_js_var stateful_click_handler(c2wasm_js_var state) {
    // Access counter from state
    int counter = c2wasm_get_object_prop_long(state, "counter");
    counter++;
    
    // Update state
    c2wasm_set_object_prop_long(state, "counter", counter);
    
    // Access the event via arguments
    c2wasm_js_var event = c2wasm_get_array_any_by_index(c2wasm_arguments, 0);
    c2wasm_js_var target = c2wasm_get_object_prop_any(event, "target");
    
    // Update element with counter value
    char buffer[32];
    sprintf(buffer, "Clicked %d times", counter);
    c2wasm_set_object_prop_string(target, "textContent", buffer);
    
    return c2wasm_undefined;
}

// Create state and handler
c2wasm_js_var state = c2wasm_create_object();
c2wasm_set_object_prop_long(state, "counter", 0);
c2wasm_js_var handler = c2wasm_create_function_with_internal_args(state, stateful_click_handler);

// Attach event listener
c2wasm_js_var listener_args = c2wasm_create_array();
c2wasm_append_array_string(listener_args, "click");
c2wasm_append_array_any(listener_args, handler);
c2wasm_call_object_prop(element, "addEventListener", listener_args);
```

### Removing Event Listeners

```c
// Store reference to the handler
c2wasm_js_var handler = c2wasm_create_function(click_handler);

// ... later, to remove the listener
c2wasm_js_var remove_listener_args = c2wasm_create_array();
c2wasm_append_array_string(remove_listener_args, "click");
c2wasm_append_array_any(remove_listener_args, handler);
c2wasm_call_object_prop(element, "removeEventListener", remove_listener_args);
```

## DOM Traversal

### Parent, Child and Sibling Navigation

```c
// Get parent node
c2wasm_js_var parent = c2wasm_get_object_prop_any(element, "parentNode");

// Get first child
c2wasm_js_var first_child = c2wasm_get_object_prop_any(element, "firstChild");

// Get last child
c2wasm_js_var last_child = c2wasm_get_object_prop_any(element, "lastChild");

// Get next sibling
c2wasm_js_var next_sibling = c2wasm_get_object_prop_any(element, "nextSibling");

// Get previous sibling
c2wasm_js_var prev_sibling = c2wasm_get_object_prop_any(element, "previousSibling");
```

### Working with Child Nodes

```c
// Get all children as NodeList
c2wasm_js_var children = c2wasm_get_object_prop_any(element, "childNodes");

// Get the number of children
long child_count = c2wasm_get_array_size(children);

// Loop through children
for(int i = 0; i < child_count; i++) {
    c2wasm_js_var child = c2wasm_get_array_any_by_index(children, i);
    
    // Do something with each child
    int node_type = c2wasm_get_object_prop_long(child, "nodeType");
    if(node_type == 1) { // 1 = Element node
        // Process element node
    }
}
```

## Advanced DOM Manipulation

### Working with Forms

```c
// Get a form element
c2wasm_js_var form = c2wasm_call_object_prop_string(c2wasm_document, "getElementById", "myForm");

// Get form input value
c2wasm_js_var input = c2wasm_call_object_prop_string(c2wasm_document, "getElementById", "username");
c2wasm_js_var value = c2wasm_get_object_prop_any(input, "value");

// Set form input value
c2wasm_set_object_prop_string(input, "value", "new-username");

// Submit form programmatically
c2wasm_js_var submit_args = c2wasm_create_array();
c2wasm_call_object_prop(form, "submit", submit_args);
```

### Working with Tables

```c
// Create a table
c2wasm_js_var create_table_args = c2wasm_create_array();
c2wasm_append_array_string(create_table_args, "table");
c2wasm_js_var table = c2wasm_call_object_prop(c2wasm_document, "createElement", create_table_args);

// Create and append a row
c2wasm_js_var create_row_args = c2wasm_create_array();
c2wasm_append_array_string(create_row_args, "tr");
c2wasm_js_var row = c2wasm_call_object_prop(c2wasm_document, "createElement", create_row_args);

// Create and append a cell
c2wasm_js_var create_cell_args = c2wasm_create_array();
c2wasm_append_array_string(create_cell_args, "td");
c2wasm_js_var cell = c2wasm_call_object_prop(c2wasm_document, "createElement", create_cell_args);

// Set cell content
c2wasm_set_object_prop_string(cell, "textContent", "Cell content");

// Append elements
c2wasm_js_var append_cell_args = c2wasm_create_array();
c2wasm_append_array_any(append_cell_args, cell);
c2wasm_call_object_prop(row, "appendChild", append_cell_args);

c2wasm_js_var append_row_args = c2wasm_create_array();
c2wasm_append_array_any(append_row_args, row);
c2wasm_call_object_prop(table, "appendChild", append_row_args);

c2wasm_js_var append_table_args = c2wasm_create_array();
c2wasm_append_array_any(append_table_args, table);
c2wasm_call_object_prop(c2wasm_body, "appendChild", append_table_args);
```

### DOM Animation

```c
// Simple animation using setTimeout
c2wasm_js_var animate_func(c2wasm_js_var state) {
    // Get the element and position from state
    c2wasm_js_var element = c2wasm_get_object_prop_any(state, "element");
    int position = c2wasm_get_object_prop_long(state, "position");
    
    // Update position
    position += 2;
    c2wasm_set_object_prop_long(state, "position", position);
    
    // Update element style
    c2wasm_js_var style = c2wasm_get_object_prop_any(element, "style");
    char pos_str[20];
    sprintf(pos_str, "%dpx", position);
    c2wasm_set_object_prop_string(style, "left", pos_str);
    
    // Continue animation if not done
    if(position < 300) {
        // Create next animation frame call
        c2wasm_js_var anim_func = c2wasm_create_function_with_internal_args(state, animate_func);
        c2wasm_js_var timeout_args = c2wasm_create_array();
        c2wasm_append_array_any(timeout_args, anim_func);
        c2wasm_append_array_long(timeout_args, 16); // ~60fps
        c2wasm_call_object_prop(c2wasm_window, "setTimeout", timeout_args);
    }
    
    return c2wasm_undefined;
}

// Start animation
c2wasm_js_var element = c2wasm_call_object_prop_string(c2wasm_document, "getElementById", "animated-element");
c2wasm_js_var style = c2wasm_get_object_prop_any(element, "style");
c2wasm_set_object_prop_string(style, "position", "absolute");
c2wasm_set_object_prop_string(style, "left", "0px");

// Create state and start animation
c2wasm_js_var state = c2wasm_create_object();
c2wasm_set_object_prop_any(state, "element", element);
c2wasm_set_object_prop_long(state, "position", 0);

// First animation call
c2wasm_js_var anim_func = c2wasm_create_function_with_internal_args(state, animate_func);
c2wasm_js_var timeout_args = c2wasm_create_array();
c2wasm_append_array_any(timeout_args, anim_func);
c2wasm_append_array_long(timeout_args, 0); // Start immediately
c2wasm_call_object_prop(c2wasm_window, "setTimeout", timeout_args);
```

## Best Practices

### Performance Optimization

- **Minimize DOM Access**: Cache DOM elements in variables instead of repeatedly querying for them
- **Batch DOM Updates**: Minimize reflows by grouping DOM changes
- **Use DocumentFragment**: When adding multiple elements, use DocumentFragment
- **Avoid Inline Styles**: When possible, manipulate classes instead of inline styles
- **Debounce Event Handlers**: For frequent events like resize or scroll

### Memory Management

- **Clean Up Event Listeners**: Remove event listeners when they're no longer needed
- **Avoid Circular References**: Be careful with closures in event handlers
- **Release DOM References**: Set variables holding DOM references to null when done

### Error Handling

- **Check Element Existence**: Always verify an element exists before manipulating it
- **Validate Input**: Sanitize any user input before inserting into the DOM
- **Provide Fallbacks**: Implement graceful degradation for missing elements

## Complete Examples

### Interactive Counter

```c
#include "c2wasm.c"
#include <stdio.h>

// Event handler function with internal state
c2wasm_js_var counter_click_handler(c2wasm_js_var state) {
    // Get current count from state
    int count = c2wasm_get_object_prop_long(state, "count");
    count++;
    
    // Update state
    c2wasm_set_object_prop_long(state, "count", count);
    
    // Update display
    c2wasm_js_var display = c2wasm_get_object_prop_any(state, "display");
    char buffer[32];
    sprintf(buffer, "Count: %d", count);
    c2wasm_set_object_prop_string(display, "textContent", buffer);
    
    return c2wasm_undefined;
}

// Main initialization function
c2wasm_js_var initialize() {
    // Create container
    c2wasm_js_var create_div_args = c2wasm_create_array();
    c2wasm_append_array_string(create_div_args, "div");
    c2wasm_js_var container = c2wasm_call_object_prop(c2wasm_document, "createElement", create_div_args);
    c2wasm_set_object_prop_string(container, "className", "counter-container");
    
    // Create display
    c2wasm_js_var create_p_args = c2wasm_create_array();
    c2wasm_append_array_string(create_p_args, "p");
    c2wasm_js_var display = c2wasm_call_object_prop(c2wasm_document, "createElement", create_p_args);
    c2wasm_set_object_prop_string(display, "textContent", "Count: 0");
    c2wasm_set_object_prop_string(display, "className", "counter-display");
    
    // Create button
    c2wasm_js_var create_btn_args = c2wasm_create_array();
    c2wasm_append_array_string(create_btn_args, "button");
    c2wasm_js_var button = c2wasm_call_object_prop(c2wasm_document, "createElement", create_btn_args);
    c2wasm_set_object_prop_string(button, "textContent", "Increment");
    c2wasm_set_object_prop_string(button, "className", "counter-button");
    
    // Append elements
    c2wasm_js_var append_display_args = c2wasm_create_array();
    c2wasm_append_array_any(append_display_args, display);
    c2wasm_call_object_prop(container, "appendChild", append_display_args);
    
    c2wasm_js_var append_button_args = c2wasm_create_array();
    c2wasm_append_array_any(append_button_args, button);
    c2wasm_call_object_prop(container, "appendChild", append_button_args);
    
    c2wasm_js_var append_container_args = c2wasm_create_array();
    c2wasm_append_array_any(append_container_args, container);
    c2wasm_call_object_prop(c2wasm_body, "appendChild", append_container_args);
    
    // Create state
    c2wasm_js_var state = c2wasm_create_object();
    c2wasm_set_object_prop_long(state, "count", 0);
    c2wasm_set_object_prop_any(state, "display", display);
    
    // Set up event listener
    c2wasm_js_var handler = c2wasm_create_function_with_internal_args(state, counter_click_handler);
    c2wasm_js_var listener_args = c2wasm_create_array();
    c2wasm_append_array_string(listener_args, "click");
    c2wasm_append_array_any(listener_args, handler);
    c2wasm_call_object_prop(button, "addEventListener", listener_args);
    
    return c2wasm_undefined;
}

int main() {
    c2wasm_start();
    
    // Set up initialization function to run when DOM is ready
    c2wasm_js_var init_func = c2wasm_create_function(initialize);
    c2wasm_js_var domready_args = c2wasm_create_array();
    c2wasm_append_array_string(domready_args, "DOMContentLoaded");
    c2wasm_append_array_any(domready_args, init_func);
    c2wasm_call_object_prop(c2wasm_document, "addEventListener", domready_args);
    
    return 0;
}
```

## See Also

- [Getting Object Properties](./getting_object_props.md)
- [Setting Object Properties](./setting_object_props.md)
- [Working with Arrays](./setting_array_props.md)
- [C2Wasm API Reference](./api_reference.md)

Working with the DOM in C2Wasm follows similar patterns to JavaScript DOM manipulation, but with a C-friendly API that handles type conversions and memory management automatically. This approach allows you to create rich, interactive web applications entirely in C code.
