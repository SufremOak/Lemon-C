#pragma once

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
        
        extern std::unordered_map<std::string, Variable> globalScope;
        extern std::vector<std::unordered_map<std::string, Variable>> scopeStack;

        void PushScope();
        void PopScope();
        bool SetVariable(const std::string& name, const Value& value, const std::string& type, bool isConst = false);
        std::optional<Value> GetVariable(const std::string& name);
    }

    // Control flow operations
    namespace ControlFlow {
        bool EvaluateCondition(const Value& condition);
        Value ExecuteIf(const Value& condition, const std::function<Value()>& ifBlock, 
                       const std::optional<std::function<Value()>>& elseBlock = std::nullopt);
        Value ExecuteWhile(const std::function<Value()>& condition, 
                         const std::function<Value()>& body);
        Value ExecuteFor(const std::function<Value()>& init,
                        const std::function<Value()>& condition,
                        const std::function<Value()>& increment,
                        const std::function<Value()>& body);
    }

    // Basic operations
    namespace Operations {
        Value Add(const Value& a, const Value& b);
        Value Subtract(const Value& a, const Value& b);
        Value Multiply(const Value& a, const Value& b);
        Value Divide(const Value& a, const Value& b);
    }

    // Function metadata
    struct FunctionMetadata {
        std::string name;
        std::vector<std::string> parameterNames;
        std::string returnType;
        std::string documentation;
    };

    // Function registry
    namespace FunctionRegistry {
        using FunctionPtr = std::function<Value(const ParameterList&)>;
        
        struct FunctionInfo {
            FunctionPtr implementation;
            FunctionMetadata metadata;
        };
        
        extern std::unordered_map<std::string, FunctionInfo> customFunctions;

        void RegisterFunction(const std::string& name, 
                            const FunctionMetadata& metadata,
                            FunctionPtr func);
        bool HasFunction(const std::string& name);
        const FunctionMetadata* GetFunctionMetadata(const std::string& name);
        Value ExecuteFunction(const std::string& name, const ParameterList& args);
    }

    // Console operations
    namespace Console {
        void Log(const char* message);
        void Error(const char* message);
        void DefineFunction(const char* name, 
                          const std::vector<std::string>& paramNames,
                          const char* returnType,
                          const char* documentation,
                          const char* body);
        void DefineSimpleFunction(const char* name, 
                                const char* paramName,
                                const char* returnType,
                                const char* documentation,
                                const char* body);
    }
} 