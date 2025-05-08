# Lemon-C
The Lemonade Clangd

## Overview
Lemon-C is a modern C language development environment that combines the power of Clangd with a fresh, user-friendly interface. It aims to make C development more accessible and enjoyable.

## Features
- Integrated Clangd support for intelligent code completion and analysis
- Modern development environment
- Cross-platform compatibility
- Python-based CLI tools for enhanced development workflow

## Prerequisites
- Python 3.x
- Clangd (or gcc/g++)
- Cython
- Other dependencies listed in `requirements.txt`

## Installation

### Using pip
```bash
pip install -r requirements.txt
python setup.py build
```

### Using make
```bash
$ make
$ sudo make install
```

### Using Nix
If you have Nix installed, you can use the provided `shell.nix`:
```bash
nix-shell
```

## Usage
See [SRC/README](./src/README.md)

## Development
1. Clone the repository
2. Install dependencies: `pip install -r requirements.txt`
3. Build the project: `make`
4. Run tests: `./build/bin/lemoncc main.🍋 -- --test-self`

## Contributing
Contributions are welcome! Please feel free to submit a Pull Request.

## License
This project is licensed under the MIT license included in the `LICENSE` file.
