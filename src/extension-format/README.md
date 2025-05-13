# Lemon-C Extension Transpiler

This project implements a parser and transpiler for the Lemon-C Extension File Format, converting it into C++ header files. The parser is built using the Pest library, and the grammar for the Lemon-C format is defined in a separate grammar file.

## Project Structure

```
lemonc-ext-transpiler
├── src
│   ├── main.rs          # Entry point of the application
│   ├── ext
│   │   ├── lang.rs      # Implementation of the parser
│   │   └── grammar.pest  # Grammar definition for Lemon-C
│   ├── parser.rs        # Additional parsing logic
│   └── transpiler.rs    # Transpiler functionality
├── Cargo.toml           # Project configuration and dependencies
└── README.md            # Project documentation
```

## Dependencies

This project uses the following dependencies:

- `pest`: A parser library for Rust.
- `pest_derive`: A procedural macro for deriving Pest parsers.

## Building the Project

To build the project, ensure you have Rust installed on your machine. Then, navigate to the project directory and run:

```bash
cargo build
```

## Running the Transpiler

After building the project, you can run the transpiler with the following command:

```bash
cargo run -- <input_file>
```

Replace `<input_file>` with the path to the Lemon-C source file you wish to transpile.

## Example Usage

To see an example of how to use the transpiler, you can create a Lemon-C source file and run the transpiler as described above. The output will be a C++ header file generated based on the input Lemon-C file.

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue for any enhancements or bug fixes.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.