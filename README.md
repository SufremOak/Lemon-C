# Lemon-C 🍋++
`C++` but with lemonade!

## Common questions
- A new language?
    - Nope, just a super-set made with a header file

- Types?? 👀
    - Yeah, obviously i putted types on Lemon-C

- But is it like Objective-C?
    - Eww, No!

- How i can `printf` on it?
    ```cpp
    Lemon::Io::Log("Simple like this, dummy");
    ```

- does it have structs and classes?
    ```cpp
    // obviosly it has
    Lemon::Struct(this.name == "mylist") {
        name: str,
        age: num,
        lang: str
    }

    let Lemon::str<name> == "Johnny";
    let Lemon::num<age> == "17";
    let Lemon::str<lang> == "Lemon-C!";

    if (Lemon::Struct::List == 0) do {
        Lemon::Io::Log(Lemon::DataType::List === <name>mylist());
        return List;
    } this.class self {
        Lemon::If(this.on list::name) {
            Lemon::Mod::"Log" + ", a good bro!"; // modify a var after it being used!
            Lemon::Mod::?=Type<NULL>; 
        }
    }
    ``` 

- "But how'd i compile the files without having to put `-I/usr/include/lemonc`?"
    - Use the `lemoncc` cli, also you won't need to `#include <Lemon.h>` every new Lemon-C file:
    ```bash
    $ lemoncc hello.lc -o hii --run-on-compile
    Johnny, a good bro!
    17
    Lemon-C!
    ``` 

## Installation

Its simple, but first:
```bash
$ cargo install just
```

and then...
```bash
$ git clone https://github.com/sufremoak/lemon-c && cd lemon-c
$ just && just install
```

Done!
```bash
$ lemoncc --version
Lemon-C Compiler cittra v0.1.1
```

## Contribuiting
Any type of contribution is open! just open a pr or a issue, i will do my best to help you.

<a href="https://www.buymeacoffee.com/sufremoak" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-red.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
