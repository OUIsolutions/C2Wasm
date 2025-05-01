<div align="center">

# C2Wasm

<img src="https://raw.githubusercontent.com/OUIsolutions/C2Wasm/main/.github/logo.png" alt="C2Wasm Logo" width="200"/>

[![Version](https://img.shields.io/badge/version-0.3.0-blue.svg)](https://github.com/OUIsolutions/C2Wasm/releases/tag/0.3.0)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Stars](https://img.shields.io/github/stars/OUIsolutions/C2Wasm?style=social)](https://github.com/OUIsolutions/C2Wasm/stargazers)

**A powerful bridge between C and the web, enabling frontend development directly in C through WebAssembly.**

</div>

## 🚀 Overview

C2Wasm is an Emscripten facilitator that provides a seamless interface between C and JavaScript. It allows developers to control JavaScript directly from C code, making it easier to develop complex frontend applications using the power and performance of C with the flexibility of web technologies.

With C2Wasm, you can:
- Manipulate the DOM directly from C code
- Handle browser events
- Create and modify JavaScript objects
- Leverage the full power of WebAssembly while writing familiar C code

<div align="center">
<img src="https://raw.githubusercontent.com/OUIsolutions/C2Wasm/main/.github/workflow.png" alt="C2Wasm Workflow" width="700"/>
</div>

## 📋 Table of Contents

- [Installation](#-installation)
- [Getting Started](#-getting-started)
- [Building From Scratch](#-building-from-scratch)
- [Documentation](#-documentation)
- [Examples](#-examples)
- [Contributing](#-contributing)
- [License](#-license)

## 🔧 Installation

### Prerequisites

- **Emscripten SDK**: C2Wasm requires the Emscripten SDK to compile C code to WebAssembly.

### Step 1: Install Emscripten

Install [Emscripten](https://github.com/emscripten-core/emsdk) by following the official documentation.

Alternatively, you can use our [quick install setup](https://github.com/mateusmoutinho/emscripten-easy-install) for a simplified installation process.

### Step 2: Add C2Wasm to Your Project

Download the latest version of [c2wasm.c](https://github.com/OUIsolutions/C2Wasm/releases/download/0.3.0/c2wasm.c) and save it in your project directory.

<div align="center">
<img src="https://raw.githubusercontent.com/OUIsolutions/C2Wasm/main/.github/installation.png" alt="Installation Process" width="600"/>
</div>

## 🏁 Getting Started

### Step 1: Create Your C File

Create a `test.c` file in the same directory where you saved `c2wasm.c`:

```c
#include "c2wasm.c"
#include <stdio.h>

long set_div_value() {
  // Create an array to hold function arguments
  c2wasm_js_var find_args = c2wasm_create_array();
  c2wasm_append_array_string(find_args, "test_div");
  
  // Get the DOM element with id "test_div"
  c2wasm_js_var element = c2wasm_call_object_prop(c2wasm_document, "getElementById", find_args);  
  
  // Set the innerHTML of the element
  c2wasm_set_object_prop_string(element, "innerHTML", "Hello World from C");
  
  return c2wasm_undefined;
}

int main() {
  // Initialize C2Wasm
  c2wasm_start();
  
  // Expose the C function to JavaScript
  c2wasm_set_object_prop_function(c2wasm_window, "set_div_value", set_div_value);
}
```

### Step 2: Compile Your C Code

Compile the C code to JavaScript using Emscripten:

```bash
emcc test.c -o test.js
```

### Step 3: Create an HTML File

Create an HTML file to test your code:

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>C2Wasm Demo</title>
    <script src="test.js"></script>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
        }
        button {
            padding: 10px 15px;
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        #test_div {
            margin: 20px 0;
            padding: 15px;
            border: 1px solid #ddd;
            border-radius: 4px;
        }
    </style>
</head>
<body>
   <h1>C2Wasm Demo</h1>
   <div id="test_div">Original Text</div> 
   <button onclick="set_div_value()">Update Text</button>
</body>
</html>
```

### Step 4: Set Up a Local Server

WebAssembly requires a server to work. You can use one of these methods:

#### Using Python

```bash
python3 -m http.server 8080
```

Then navigate to [http://localhost:8080/test.html](http://localhost:8080/test.html)

#### Using Yahr (Alternative)

If you don't have Python, you can use [Yahr](https://github.com/OUIsolutions/yahr):

```bash
yahr
```

<div align="center">
<img src="https://raw.githubusercontent.com/OUIsolutions/C2Wasm/main/.github/demo.gif" alt="C2Wasm Demo" width="600"/>
</div>

## 🔨 Building From Scratch

If you want to build `c2wasm.c` from source, you'll need [Darwin](https://github.com/OUIsolutions/Darwin) version **0.2.1** or later.

### Step 1: Install Darwin

```bash
curl -L https://github.com/OUIsolutions/Darwin/releases/download/0.2.1/darwin.out -o darwin.out && sudo chmod +x darwin.out && sudo mv darwin.out /usr/bin/darwin
```

### Step 2: Build C2Wasm

```bash
darwin run_blueprint
```

## 📚 Documentation

| Topic | Description |
|-------|-------------|
| [Setting Object Properties](docs/setting_object_props.md) | Learn how to set properties on JavaScript objects from C |
| [Setting Array Properties](docs/setting_array_props.md) | Detailed guide on manipulating JavaScript arrays |
| [Getting Object Properties](docs/getting_object_props.md) | How to retrieve properties from JavaScript objects |
| [Getting Array Properties](docs/getting_array_props.md) | Methods for accessing JavaScript array elements |
| [Working with DOM](docs/working_with_dom.md) | Techniques for DOM manipulation from C |

## 💡 Examples

| Example | Description |
|---------|-------------|
| [Accumulator](/examples/acumulator/) | Implementation of a JavaScript accumulator object created in C |
| [Array Set](/examples/array_set/) | Demonstrates setting values in JavaScript arrays |
| [Array Append](/examples/array_append/) | Shows how to append elements to JavaScript arrays |
| [Array Iteration](/examples/array_iteration/) | Methods for iterating through JavaScript arrays | 
| [Object Iteration](/examples/object_iteration/) | Techniques for iterating through JavaScript objects |
| [Object Set Any](/examples/object_set_any/) | Set any value type to a JavaScript object |
| [Object Set](/examples/object_set/) | Basic object property manipulation |

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
