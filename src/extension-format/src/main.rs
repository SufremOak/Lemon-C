// This is the entry point of the Lemon-C Extension File Format transpiler.
// It initializes the parser and transpiler, processes input files, and handles the overall flow of the program.

use std::env;
use std::fs;
use std::process;

mod transpiler;
mod parser;
mod ext;

use transpiler::transpile;

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        eprintln!("Usage: {} <input_file>", args[0]);
        process::exit(1);
    }

    let input_file = &args[1];
    let source = fs::read_to_string(input_file).unwrap_or_else(|err| {
        eprintln!("Error reading file {}: {}", input_file, err);
        process::exit(1);
    });

    match ext::lang::parse_source(&source) {
        Ok(pairs) => {
            let cpp_code = transpile(pairs);
            let output_file = format!("{}.hpp", input_file);
            fs::write(output_file, cpp_code).unwrap_or_else(|err| {
                eprintln!("Error writing output file: {}", err);
                process::exit(1);
            });
        }
        Err(err) => {
            eprintln!("Parsing error: {}", err);
            process::exit(1);
        }
    }
}