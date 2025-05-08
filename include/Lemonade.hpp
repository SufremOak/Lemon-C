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

} // End of namespace Lemon

#endif // LEMON_C_H

/*
  How to "use" Lemon-C:
  1.  Include this header in your C++ file: #include "lemon_c.h"
  2.  Use the  functions and macros.  Example:

  #include <iostream>
  #include "lemon_c.h"
  #include <cmath>

  int main() {
      Lemon::Log("Hello, Lemon-C World!");
      std::string result = Lemon::concat("Lemon", "-C");
      Lemon::Log(std::to_string(Lemon::pow(2, 3)));

      Lemon::vector<int> numbers = {1, 2, 3, 4};
      for_(i, 0, 5) {
        Lemon::Log("Loop iteration: " + std::to_string(i));
      }

      int counter = 0;
      while_(counter < 3) {
        Lemon::Log("While loop: " + std::to_string(counter));
        counter++;
      }
      int sum = Lemon::add(5, 6);
      Lemon::Log(std::to_string(sum));

      std::string num_str = "12345";
      int num = Lemon::string_to_int(num_str);
      Lemon::Log(std::to_string(num));

      num_str = "abc";
      int num = Lemon::string_to_int(num_str);
      Lemon::Log(std::to_string(num));

      Lemon::Log(std::to_string(Lemon::abs(-10.5)));
      Lemon::Log(std::to_string(Lemon::abs(7)));
      Lemon::Log(std::to_string(Lemon::max(10, 5)));
      Lemon::Log(std::to_string(Lemon::min(10, 5)));

      std::string text = "Hello, world!";
      if (Lemon::contains(text, "world")) {
          Lemon::Log("Found 'world' in the text.");
      } else {
          Lemon::Log("Did not find 'world'.");
      }

      std::string csv_data = "apple,banana,orange";
      std::vector<std::string> fruits = Lemon::split(csv_data, ',');
      for (const auto& fruit : fruits) {
          Lemon::Log(fruit);
      }
      std::string text_to_trim = "   trim me   ";
      std::string trimmed_text = Lemon::trim(text_to_trim);
      Lemon::Log(trimmed_text);

      // Example of using the object system:
      std::shared_ptr<Lemon::object> str_obj = Lemon::create_object("string", "Hello, Lemon-C Object!");
      std::shared_ptr<Lemon::object> num_obj = Lemon::create_object("number", "123.45");
      std::shared_ptr<Lemon::object> num_obj2 = Lemon::create_object("number", 567.89");

      if (str_obj) {
          str_obj->print();
          Lemon::Log("Type: " + str_obj->type_name());
      }
      if (num_obj) {
          num_obj->print();
          Lemon::Log("Type: " + num_obj->type_name());
      }
      if (num_obj2) {
          num_obj2->print();
          Lemon::Log("Type: " + num_obj2->type_name());
      }

      // Example of using the class system
      std::shared_ptr<Lemon::person> person1 = Lemon::create_person("Alice", 30);
      std::shared_ptr<Lemon::person> person2 = Lemon::create_person("Bob", 25);

      if (person1) {
          person1->print();
          Lemon::Log("Type: " + person1->type_name());
      }
      if (person2) {
          person2->print();
          Lemon::Log("Type: " + person2->type_name());
      }
      std::shared_ptr<Lemon::circle> circle1 = Lemon::create_circle(5.0);
      if (circle1) {
          circle1->print();
          Lemon::Log("Type: " + circle1->type_name());
          Lemon::Log("Area: " + std::to_string(circle1->get_area()));
      }
      // Example of using the addition operator
      std::shared_ptr<Lemon::object> num1 = Lemon::create_object("number", "10");
      std::shared_ptr<Lemon::object> num2 = Lemon::create_object("number", "20");
      std::shared_ptr<Lemon::object> result_num = num1->add(num2);
      if (result_num) {
          result_num->print();
      }

      std::shared_ptr<Lemon::object> str1 = Lemon::create_object("string", "Hello, ");
      std::shared_ptr<Lemon::object> str2 = Lemon::create_object("string", "World!");
      std::shared_ptr<Lemon::object> result_str = str1->add(str2);
      if (result_str) {
          result_str->print();
      }

    // Example of using the @class macro
    Lemon::person p1("Charlie", 35);
    p1.print();

    Lemon::circle c1(7.5);
    c1.print();

    // Example of using interfaces
    Lemon::interface_serializable* ser = &p1;
    Lemon::Log("Serialized Person: " + ser->serialize());

    Lemon::interface_cloneable* cloner = &c1;
    std::shared_ptr<Lemon::object> cloned_circle = cloner->clone();
    if (cloned_circle) {
        cloned_circle->print();
        Lemon::Log("Type of cloned object: " + cloned_circle->type_name());
    }

      // Example of the new syntax
      Lemon::func(int, my_function, (int a, int b)) {
          return a + b;
      }
      Lemon::Log(std::to_string(my_function(10, 20)));

      return 0;
  }
*/

