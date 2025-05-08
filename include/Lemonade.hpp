#ifndef LEMON_C_H
#define LEMON_C_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <map>
#include <memory> // For smart pointers

// Lemon-C:  "Flavor" of C++ with a more eye-friendly syntax

namespace Lemon {

    // 1. Basic Output (Lemon-C's "Log")
    void Log(const std::string& text) {
        std::cout << text << std::endl;
    }

    // 2. String Concatenation (Lemon-C's "+" for strings)
    std::string concat(const std::string& str1, const std::string& str2) {
        return str1 + str2;
    }

    // 3. Simple Math Function (Lemon-C's "pow")
    double pow(double base, double exponent) {
        return std::pow(base, exponent);
    }

    // 4.  Data Structures
    template <typename T>
    using vector = std::vector<T>;

    template <typename K, typename V>
    using map = std::map<K, V>;

    // 5.  Control Flow (Macros for a different look)
    #define for_(variable, start_value, end_value) \
        for (int variable = start_value; variable < end_value; ++variable)

    #define while_(condition) \
        while (condition)

    // 6. Function definition
    #define func(return_type, name, args) \
        return_type name args

    // 7.  Absolute value
    double abs(double x) {
        return std::abs(x);
    }

    // 8. Find max of two numbers
    double max(double a, double b) {
        return std::max(a, b);
    }

    // 9. Find min of two numbers.
    double min(double a, double b) {
        return std::min(a, b);
    }
    // 10. Check if a string contains a substring.
    bool contains(const std::string& str, const std::string& sub) {
        return str.find(sub) != std::string::npos;
    }

    // 11. Split a string by a delimiter.
    std::vector<std::string> split(const std::string& str, const char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    // 12.  Trim whitespace from both ends of a string
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (std::string::npos == first) {
            return "";
        }
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, (last - first + 1));
    }

    // 13. String to int
    int string_to_int(const std::string& str) {
        try {
            return std::stoi(str);
        } catch (const std::invalid_argument& e) {
            return 0;
        }
    }

    // 14.  Basic Type System
    class object {
    public:
        virtual ~object() {}
        virtual void print() const {
            Log("Base Object");
        }
        virtual std::string type_name() const {
            return "object";
        }
        virtual std::shared_ptr<object> add(const std::shared_ptr<object>& other) const {
            return nullptr;
        }
    };

    class string_obj : public object {
    public:
        std::string value;
        string_obj(const std::string& val) : value(val) {}
        void print() const override {
            Log(value);
        }
        std::string type_name() const override {
            return "string";
        }
        std::shared_ptr<object> add(const std::shared_ptr<object>& other) const override {
            if (other->type_name() == "string") {
                std::shared_ptr<string_obj> other_str = std::dynamic_pointer_cast<string_obj>(other);
                if (other_str) {
                    return std::make_shared<string_obj>(this->value + other_str->value);
                }
            }
            return nullptr;
        }
    };

    class number_obj : public object {
    public:
        double value;
        number_obj(double val) : value(val) {}
        void print() const override {
            Log(std::to_string(value));
        }
        std::string type_name() const override {
            return "number";
        }
        std::shared_ptr<object> add(const std::shared_ptr<object>& other) const override {
            if (other->type_name() == "number") {
                std::shared_ptr<number_obj> other_num = std::dynamic_pointer_cast<number_obj>(other);
                if (other_num) {
                    return std::make_shared<number_obj>(this->value + other_num->value);
                }
            }
            return nullptr;
        }
    };

    // 15. Object Creation
    std::shared_ptr<object> create_object(const std::string& type, const std::string& value) {
        if (type == "string") {
            return std::make_shared<string_obj>(value);
        } else if (type == "number") {
            try {
                double num_value = std::stod(value);
                return std::make_shared<number_obj>(num_value);
            } catch (const std::invalid_argument& e) {
                return nullptr;
            }
        }
        return nullptr;
    }
    std::shared_ptr<object> create_object(const std::string& type, double value) {
        if (type == "number") {
            return std::make_shared<number_obj>(value);
        }
        return nullptr;
    }

    // 16. Class Definitions (using macros for a different look)
    #define class_(name) \
    class name : public Lemon::object { \
    public:

    #define private_ 멤버: \
    private:

    #define public_ 멤버: \
    public:

    #define constructor_(args) \
        name(args) :

    #define method_(definition) \
        definition override

    // 17. Interface Support (using abstract classes)
    class interface_serializable {
    public:
        virtual ~interface_serializable() {}
        virtual std::string serialize() const = 0;
    };

    class interface_cloneable {
    public:
        virtual ~interface_cloneable() {}
        virtual std::shared_ptr<object> clone() const = 0;
    };

    // 18. Implementing Interfaces
    class person : public object, public interface_serializable, public interface_cloneable {
    public:
        std::string name;
        int age;

        constructor_(const std::string& name, int age)  // constructor
            name(name), age(age) {}

        method_(void print() const)  // method
        {
            Log("Person: " + name + ", Age: " + std::to_string(age));
        }
        std::string type_name() const override {
            return "person";
        }

        std::string serialize() const override {
            return "Person { name: " + name + ", age: " + std::to_string(age) + " }";
        }

        std::shared_ptr<object> clone() const override {
            return std::make_shared<person>(name, age);
        }
    };

    class circle : public object, public interface_cloneable {
    public:
        double radius;
        constructor_(double radius)
            radius(radius) {}
        method_(void print() const) {
            Log("Circle with radius: " + std::to_string(radius));
        }
        std::string type_name() const override {
            return "circle";
        }

        double get_area() const {
            return M_PI * radius * radius;
        }
        std::shared_ptr<object> clone() const override {
            return std::make_shared<circle>(radius);
        }
    };

    // 19. Object Creation
    std::shared_ptr<person> create_person(const std::string& name, int age) {
        return std::make_shared<person>(name, age);
    }

    std::shared_ptr<circle> create_circle(double radius) {
        return std::make_shared<circle>(radius);
    }
}}
#endif // LEMON_C_H
