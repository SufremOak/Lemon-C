{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.python3
    pkgs.python3Packages.typer
    pkgs.zig
    pkgs.gcc
  ];

  shellHook = ''
    echo "Welcome to the Lemonade development environment!"
    echo "You can use 'lemonadecli.py' for Python-based commands and 'lemoc.zig' for Zig-based commands."
  '';
}
