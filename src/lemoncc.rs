use std::env;
use env::args;
use std::process::Command;

fn configure_environment() -> (String, String, String) {
    if cfg!(target_os = "windows") {
        // Windows-specific configuration
        let cxx = "cl".to_string();
        let cxxflags = "/std:c++17 /O2 /I C:\\LemonC\\include".to_string();
        let ldflags = "/link /LIBPATH:C:\\LemonC\\lib".to_string();

        // Set environment variables for MSVC
        let status = Command::new("cmd")
            .args(&["/C", "set", "INCLUDE=C:\\LemonC\\include;%INCLUDE%"])
            .status()
            .expect("Failed to set INCLUDE environment variable");

        if !status.success() {
            eprintln!("Failed to configure MSVC environment");
            std::process::exit(1);
        }

        (cxx, cxxflags, ldflags)
    } else {
        // Unix-like systems (Linux, macOS)
        let cxx = "gcc".to_string();
        let cxxflags = "-std=c++11 -O2 -I/usr/local/include/LemonC".to_string();
        let ldflags = "-lm -lpthread".to_string();

        (cxx, cxxflags, ldflags)
    }
}

pub fn print_help() {
     println!("Usage: {} [OPTIONS] <your arguments>", env::args().next().unwrap_or_default());
                println!("Options:");
                println!("  --help       Show this help message");
                println!("  --version    Show the version of the application");
                println!("  --run-on-compile    Compile and run the program");
                println!("  --compile <file.lc>   Compile the program without running it");
                println!("  -o <output>    Specify the output file name");
}

fn main() {
    let (cxx, cxxflags, ldflags) = configure_environment();

    // Collect command-line arguments
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        print_help();
        eprintln!("Error: No arguments provided");
        std::process::exit(1);
    }

    // Check if the first argument is a file
    if args[1].ends_with(".lc") {
        // Compile the file
        let file_name = &args[1];
        let output_file = file_name.replace(".lc", ".o");
        let compile_command = format!(
            "{} {} {} -o {} {}",
            cxx, cxxflags, file_name, output_file, ldflags
        );

        let status = Command::new("sh")
            .arg("-c")
            .arg(compile_command)
            .status()
            .expect("Failed to compile the file");

        if !status.success() {
            eprintln!("Compilation failed");
            std::process::exit(1);
        }

        // Run the compiled program
        let run_command = format!("./{}", output_file);
        let status = Command::new("sh")
            .arg("-c")
            .arg(run_command)
            .status()
            .expect("Failed to run the program");

        if !status.success() {
            eprintln!("Execution failed");
            std::process::exit(1);
        }
    } else {
        // Handle special commands
        match args[1].as_str() {
            "--help" => {
               print_help();
            }
            "--version" => {
                println!("{} version 0.1.1 cittra-dev", args[0]);
            }
            _ => {
                // Print the arguments
                println!("Arguments passed:");
                for (i, arg) in args.iter().enumerate().skip(1) {
                    println!("Argument {}: {}", i, arg);
                }
            }
        }
    }
}