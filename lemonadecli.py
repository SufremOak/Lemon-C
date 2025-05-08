import typer
import subprocess
import json
import os

app = typer.Typer()

@app.command()
def new(help: str = "Create a new Lemonfile with a main.🍋 file"):
    # check if the directory is empty, if not just ask the user for a filename and don't create a Lemonfile
    if os.path.exists("Lemonfile"):
        if os.path.getsize("Lemonfile") > 0:
            typer.echo("Lemonfile already exists. Please remove it or use a different name.")
            raise typer.Exit()
    # create a new Lemonfile
    with open("Lemonfile", "w") as f:
        f.write("# Lemonfile\n")
    # create a new main.🍋 file
    with open("main.🍋", "w") as f:
        f.write('#include <Lemonade.hpp>\nLemon::Log("Hello, World!");\n')
    typer.echo("Lemonfile and main.🍋 created.")    

@app.command()
def build(help="Build the Lemonfile"):
    # check if the Lemonfile exists
    if not os.path.exists("Lemonfile"):
        typer.echo("Lemonfile does not exist. Please create one first.")
        raise typer.Exit()
    # build the Lemonfile
    subprocess.run(["lemoc", "build", "Lemonfile"], check=True)
    typer.echo("Lemonfile built.")

@app.command()
def check(
    help: str="Check an lemon file for including errors",
    file: str = typer.Argument("Lemonfile", help="The Lemonfile to check")):
    # check if the Lemonfile exists
    if not os.path.exists(file):
        typer.echo(f"{file} does not exist.")
        raise typer.Exit()
    # check the Lemonfile
    result = subprocess.run(["lemoc", "check", file], capture_output=True, text=True)
    if result.returncode == 0:
        typer.echo("No errors found.")
    else:
        typer.echo(result.stderr)
        raise typer.Exit()

if __name__ == "__main__":
    app()