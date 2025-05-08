/*
    The baselang module for Lemon-C
    Includes:
        | Basic handling
        | Built-in functions
        | Standard library (via the C++ standard library)
        | `Lemon` Namespace
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <variant>
#include <memory>
#include <sstream>
#include <any>
#include <optional>

namespace Lemon {
    # ifdef _cplusplus
    extern "C" {}
    # endif

    // Type system for function parameters
    using Value = std::variant<int, double, std::string, bool>;
    using ParameterList = std::vector<Value>;
    
    // Variable system
    namespace Variables {
        struct Variable {
            Value value;
            std::string type;
            bool isConst;
        };
        
        std::unordered_map<std::string, Variable> globalScope;
        std::vector<std::unordered_map<std::string, Variable>> scopeStack;

        void PushScope() {
            scopeStack.push_back({});
        }

        void PopScope() {
            if (!scopeStack.empty()) {
                scopeStack.pop_back();
            }
        }

        bool SetVariable(const std::string& name, const Value& value, const std::string& type, bool isConst = false) {
            if (scopeStack.empty()) {
                if (globalScope.find(name) != globalScope.end() && globalScope[name].isConst) {
                    return false;
                }
                globalScope[name] = {value, type, isConst};
                return true;
            }

            auto& currentScope = scopeStack.back();
            if (currentScope.find(name) != currentScope.end() && currentScope[name].isConst) {
                return false;
            }
            currentScope[name] = {value, type, isConst};
            return true;
        }

        std::optional<Value> GetVariable(const std::string& name) {
            // Check current scope
            if (!scopeStack.empty()) {
                auto& currentScope = scopeStack.back();
                if (currentScope.find(name) != currentScope.end()) {
                    return currentScope[name].value;
                }
            }
            
            // Check global scope
            if (globalScope.find(name) != globalScope.end()) {
                return globalScope[name].value;
            }
            
            return std::nullopt;
        }
    }

    // Control flow operations
    namespace ControlFlow {
        bool EvaluateCondition(const Value& condition) {
            return std::visit([](const auto& v) -> bool {
                if constexpr (std::is_same_v<std::decay_t<decltype(v)>, bool>) {
                    return v;
                }
                return false;
            }, condition);
        }

        Value ExecuteIf(const Value& condition, const std::function<Value()>& ifBlock, 
                       const std::optional<std::function<Value()>>& elseBlock = std::nullopt) {
            if (EvaluateCondition(condition)) {
                return ifBlock();
            } else if (elseBlock) {
                return (*elseBlock)();
            }
            return Value{};
        }

        Value ExecuteWhile(const std::function<Value()>& condition, 
                         const std::function<Value()>& body) {
            Value result;
            while (EvaluateCondition(condition())) {
                result = body();
            }
            return result;
        }

        Value ExecuteFor(const std::function<Value()>& init,
                        const std::function<Value()>& condition,
                        const std::function<Value()>& increment,
                        const std::function<Value()>& body) {
            Value result;
            for (init(); EvaluateCondition(condition()); increment()) {
                result = body();
            }
            return result;
        }
    }

    // Basic operations
    namespace Operations {
        Value Add(const Value& a, const Value& b) {
            return std::visit([](const auto& v1, const auto& v2) -> Value {
                if constexpr (std::is_same_v<std::decay_t<decltype(v1)>, int> &&
                            std::is_same_v<std::decay_t<decltype(v2)>, int>) {
                    return v1 + v2;
                }
                if constexpr (std::is_same_v<std::decay_t<decltype(v1)>, double> &&
                            std::is_same_v<std::decay_t<decltype(v2)>, double>) {
                    return v1 + v2;
                }
                if constexpr (std::is_same_v<std::decay_t<decltype(v1)>, std::string> &&
                            std::is_same_v<std::decay_t<decltype(v2)>, std::string>) {
                    return v1 + v2;
                }
                throw std::runtime_error("Invalid types for addition");
            }, a, b);
        }

        Value Subtract(const Value& a, const Value& b) {
            return std::visit([](const auto& v1, const auto& v2) -> Value {
                if constexpr (std::is_same_v<std::decay_t<decltype(v1)>, int> &&
                            std::is_same_v<std::decay_t<decltype(v2)>, int>) {
                    return v1 - v2;
                }
                if constexpr (std::is_same_v<std::decay_t<decltype(v1)>, double> &&
                            std::is_same_v<std::decay_t<decltype(v2)>, double>) {
                    return v1 - v2;
                }
                throw std::runtime_error("Invalid types for subtraction");
            }, a, b);
        }

        Value Multiply(const Value& a, const Value& b) {
            return std::visit([](const auto& v1, const auto& v2) -> Value {
                if constexpr (std::is_same_v<std::decay_t<decltype(v1)>, int> &&
                            std::is_same_v<std::decay_t<decltype(v2)>, int>) {
                    return v1 * v2;
                }
                if constexpr (std::is_same_v<std::decay_t<decltype(v1)>, double> &&
                            std::is_same_v<std::decay_t<decltype(v2)>, double>) {
                    return v1 * v2;
                }
                throw std::runtime_error("Invalid types for multiplication");
            }, a, b);
        }

        Value Divide(const Value& a, const Value& b) {
            return std::visit([](const auto& v1, const auto& v2) -> Value {
                if constexpr (std::is_same_v<std::decay_t<decltype(v1)>, int> &&
                            std::is_same_v<std::decay_t<decltype(v2)>, int>) {
                    if (v2 == 0) throw std::runtime_error("Division by zero");
                    return v1 / v2;
                }
                if constexpr (std::is_same_v<std::decay_t<decltype(v1)>, double> &&
                            std::is_same_v<std::decay_t<decltype(v2)>, double>) {
                    if (v2 == 0.0) throw std::runtime_error("Division by zero");
                    return v1 / v2;
                }
                throw std::runtime_error("Invalid types for division");
            }, a, b);
        }
    }

    // Function metadata
    struct FunctionMetadata {
        std::string name;
        std::vector<std::string> parameterNames;
        std::string returnType;
        std::string documentation;
    };

    // Function registry to store custom functions
    namespace FunctionRegistry {
        using FunctionPtr = std::function<Value(const ParameterList&)>;
        
        struct FunctionInfo {
            FunctionPtr implementation;
            FunctionMetadata metadata;
        };
        
        std::unordered_map<std::string, FunctionInfo> customFunctions;

        void RegisterFunction(const std::string& name, 
                            const FunctionMetadata& metadata,
                            FunctionPtr func) {
            customFunctions[name] = {func, metadata};
        }

        bool HasFunction(const std::string& name) {
            return customFunctions.find(name) != customFunctions.end();
        }

        const FunctionMetadata* GetFunctionMetadata(const std::string& name) {
            auto it = customFunctions.find(name);
            return it != customFunctions.end() ? &it->second.metadata : nullptr;
        }

        Value ExecuteFunction(const std::string& name, const ParameterList& args) {
            auto it = customFunctions.find(name);
            if (it == customFunctions.end()) {
                throw std::runtime_error("Function '" + name + "' not found");
            }

            const auto& metadata = it->second.metadata;
            if (args.size() != metadata.parameterNames.size()) {
                throw std::runtime_error("Invalid number of arguments for function '" + name + "'");
            }

            try {
                Variables::PushScope();
                // Set function parameters as variables in the new scope
                for (size_t i = 0; i < args.size(); ++i) {
                    Variables::SetVariable(metadata.parameterNames[i], args[i], "auto");
                }
                auto result = it->second.implementation(args);
                Variables::PopScope();
                return result;
            } catch (const std::exception& e) {
                Variables::PopScope();
                throw std::runtime_error("Error executing function '" + name + "': " + e.what());
            }
        }
    }

    // Lemon::Console
    namespace Console {
        void Log(const char* message) {
            #ifdef _cplusplus
                std::cout << message << std::endl;
            #else
                printf("%s\n", message);
            #endif
        }

        void Error(const char* message) {
            #ifdef _cplusplus
                std::cerr << "Error: " << message << std::endl;
            #else
                fprintf(stderr, "Error: %s\n", message);
            #endif
        }

        void DefineFunction(const char* name, 
                          const std::vector<std::string>& paramNames,
                          const char* returnType,
                          const char* documentation,
                          const char* body) {
            
            FunctionMetadata metadata{
                name,
                paramNames,
                returnType,
                documentation
            };

            auto func = [body](const ParameterList& args) -> Value {
                std::stringstream ss;
                ss << "Executing function with " << args.size() << " parameters\n";
                
                for (size_t i = 0; i < args.size(); ++i) {
                    ss << "Parameter " << i << ": ";
                    std::visit([&ss](const auto& v) {
                        ss << v;
                    }, args[i]);
                    ss << "\n";
                }

                ss << "Function body: " << body;
                return std::string(ss.str());
            };
            
            FunctionRegistry::RegisterFunction(name, metadata, func);
        }

        void DefineSimpleFunction(const char* name, 
                                const char* paramName,
                                const char* returnType,
                                const char* documentation,
                                const char* body) {
            DefineFunction(name, {paramName}, returnType, documentation, body);
        }
    }
}