use std::env;
use std::process::Command;
use std::fs;
use std::fs::{self, Write};

if os.name() == "windows" {
    // Windows-specific code
    use std::os::windows::process::CommandExt;
    use std::os::windows::fs::FileExt;
    use std::os::windows::fs::OpenOptionsExt;
    use std::os::windows::fs::File;

    let cxx = "cl";
    let cxxflags = format!("{} -I/usr/local/include/LemonC -DWIN32", cxxflags);
} else {
    // Unix-like systems (Linux, macOS)
    use std::os::unix::process::CommandExt;
    use std::os::unix::fs::FileExt;
    use std::os::unix::fs::OpenOptionsExt;
    use std::os::unix::fs::File;

    let version = "0.1.1";
    let cxx = "gcc";
    let cxxflags = "-std=c++11 -O2";
    let ldflags = "-lm -lpthread";
    let cxxflags = format!("{} -I/usr/local/include/LemonC", cxxflags);
}

fn main() {
    // Collect command-line arguments
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        eprintln!("Usage: {} [OPTIONS] <your arguments>", args[0]);
        std::process::exit(1);
    }
    // Check if the first argument is a file
    if args[1].ends_with(".lc") {
        // Compile the file
        let file_name = &args[1];
        let output_file = file_name.replace(".lc", ".o");
        let compile_command = format!("{} {} -o {}", cxx, file_name, output_file);
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
    }
    // Handle special commands
    match args[1].as_str() {
        "--help" => {
            println!("Usage: {} [OPTIONS] <your arguments>", args[0]);
            println!("Options:");
            println!("  --help       Show this help message");
            println!("  --version    Show the version of the application");
            println!("  --run-on-compile    Compile and run the program");
            println("   --compile <file.lc>   Compile the program without running it");
            println!("  -o <output>    Specify the output file name");
        }
        "--version" => {
            println!("{} version 1.0.0", args[0]);
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