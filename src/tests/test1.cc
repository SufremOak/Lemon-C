#include "Lemon.h"

// Variables
Lemon::Variables::SetVariable("x", 42, "int");
Lemon::Variables::SetVariable("name", std::string("John"), "string", true); // const

// Control Flow
Lemon::ControlFlow::ExecuteIf(
    true,  // condition
    []() -> Lemon::Value { return 42; },  // if block
    []() -> Lemon::Value { return 0; }    // else block
);

// While Loop
Lemon::ControlFlow::ExecuteWhile(
    []() -> Lemon::Value { return true; },  // condition
    []() -> Lemon::Value { return 42; }     // body
);

// For Loop
Lemon::ControlFlow::ExecuteFor(
    []() -> Lemon::Value { return 0; },     // init
    []() -> Lemon::Value { return true; },  // condition
    []() -> Lemon::Value { return 0; },     // increment
    []() -> Lemon::Value { return 42; }     // body
);

// Basic Operations
auto sum = Lemon::Operations::Add(5, 3);
auto diff = Lemon::Operations::Subtract(10, 4);
auto product = Lemon::Operations::Multiply(6, 7);
auto quotient = Lemon::Operations::Divide(20, 4);

// String Operations
auto greeting = Lemon::Operations::Add(std::string("Hello, "), std::string("World!"));