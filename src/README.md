# Lemon-C SDK

Lemon-C is a lightweight, embeddable programming language implementation that provides a flexible runtime environment for C++ applications. It offers a rich set of features including variable management, control flow operations, and custom function definitions.

## Features

- **Variable System**: Global and local scopes with type information
- **Control Flow**: If-else, while, and for loops
- **Basic Operations**: Arithmetic and string operations
- **Function System**: Custom function definition and execution
- **Console Operations**: Logging and error reporting

## Installation

### Using CMake

1. Include the SDK in your project:
```cmake
find_package(LemonC REQUIRED)
target_link_libraries(your_target PRIVATE lemonc)
```

2. Include the header in your code:
```cpp
#include <lemonc/Baselang.h>
```

## Usage Examples

### Basic Console Operations

```cpp
// Logging
Lemon::Console::Log("Hello, World!");

// Error reporting
Lemon::Console::Error("Something went wrong");
```

### Variable Management

```cpp
// Setting variables
Lemon::Variables::SetVariable("x", 42, "int");
Lemon::Variables::SetVariable("name", std::string("John"), "string", true); // const

// Getting variables
auto value = Lemon::Variables::GetVariable("x");
if (value) {
    std::visit([](const auto& v) {
        std::cout << "Value: " << v << std::endl;
    }, *value);
}
```

### Control Flow

```cpp
// If-else
Lemon::ControlFlow::ExecuteIf(
    true,
    []() -> Lemon::Value { return 42; },
    []() -> Lemon::Value { return 0; }
);

// While loop
Lemon::ControlFlow::ExecuteWhile(
    []() -> Lemon::Value { return true; },
    []() -> Lemon::Value { return 42; }
);
```

### Custom Functions

```cpp
// Define a function
Lemon::Console::DefineFunction(
    "greet",
    {"name"},
    "string",
    "Greets a person by name",
    "return 'Hello, ' + name;"
);

// Execute the function
auto result = Lemon::FunctionRegistry::ExecuteFunction("greet", {
    Lemon::Value(std::string("John"))
});
```

### Basic Operations

```cpp
// Arithmetic operations
auto sum = Lemon::Operations::Add(5, 3);
auto diff = Lemon::Operations::Subtract(10, 4);
auto product = Lemon::Operations::Multiply(6, 7);
auto quotient = Lemon::Operations::Divide(20, 4);

// String operations
auto greeting = Lemon::Operations::Add(
    std::string("Hello, "),
    std::string("World!")
);
```

## API Reference

### Namespaces

- `Lemon::Variables`: Variable management
- `Lemon::ControlFlow`: Control flow operations
- `Lemon::Operations`: Basic operations
- `Lemon::FunctionRegistry`: Function management
- `Lemon::Console`: Console operations

### Types

- `Lemon::Value`: Variant type for all supported values
- `Lemon::ParameterList`: Vector of values for function parameters
- `Lemon::FunctionMetadata`: Function metadata structure

## Error Handling

The SDK uses exceptions for error handling. Always wrap SDK calls in try-catch blocks:

```cpp
try {
    // SDK operations
} catch (const std::exception& e) {
    Lemon::Console::Error(e.what());
}
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

```sh
$ lemoncc example.🍋 --cpp
[lemond] Changing file extension from `.🍋` to `.cc`
[lemond] Running g++
[g++] g++ example.cc -I/usr/include/lemon -Wall -Shared -Wextra
[lemoncc] Starting ./a.out

```