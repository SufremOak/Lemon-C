#include <iostream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

class LemonCC {
private:
    std::string inputFile;
    std::vector<std::string> compilerFlags;
    bool shouldRun = false;
    bool shouldTest = false;

    void printUsage() const {
        std::cout << "Usage: lemoncc <input_file> [options]\n"
                  << "Options:\n"
                  << "  --cpp        Convert to C++ and compile\n"
                  << "  --run        Run the compiled program\n"
                  << "  --test-self  Run self-tests\n"
                  << "  --help       Show this help message\n";
    }

    std::string changeExtension(const std::string& filename, const std::string& newExt) {
        fs::path path(filename);
        return path.replace_extension(newExt).string();
    }

    bool compile(const std::string& sourceFile) {
        std::string cmd = "g++ " + sourceFile + " -I/usr/include/lemon -Wall -Wextra";
        
        // Add any additional compiler flags
        for (const auto& flag : compilerFlags) {
            cmd += " " + flag;
        }

        std::cout << "[g++] " << cmd << std::endl;
        return system(cmd.c_str()) == 0;
    }

    bool runProgram() {
        std::cout << "[lemoncc] Starting ./a.out" << std::endl;
        return system("./a.out") == 0;
    }

public:
    LemonCC(int argc, char* argv[]) {
        if (argc < 2) {
            printUsage();
            exit(1);
        }

        inputFile = argv[1];
        
        // Parse command line arguments
        for (int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "--cpp") {
                // Handle C++ conversion
            } else if (arg == "--run") {
                shouldRun = true;
            } else if (arg == "--test-self") {
                shouldTest = true;
            } else if (arg == "--help") {
                printUsage();
                exit(0);
            } else {
                compilerFlags.push_back(arg);
            }
        }
    }

    bool execute() {
        // Check if input file exists
        if (!fs::exists(inputFile)) {
            std::cerr << "Error: Input file '" << inputFile << "' not found." << std::endl;
            return false;
        }

        // Handle .🍋 extension
        if (inputFile.find(".🍋") != std::string::npos) {
            std::string cppFile = changeExtension(inputFile, ".cc");
            std::cout << "[lemond] Changing file extension from `.🍋` to `.cc`" << std::endl;
            std::cout << "[lemond] Running g++" << std::endl;
            
            if (!compile(cppFile)) {
                std::cerr << "Compilation failed." << std::endl;
                return false;
            }

            if (shouldRun) {
                return runProgram();
            }
        } else {
            std::cerr << "Error: Input file must have .🍋 extension." << std::endl;
            return false;
        }

        return true;
    }
};

int main(int argc, char* argv[]) {
    LemonCC compiler(argc, argv);
    return compiler.execute() ? 0 : 1;
}
