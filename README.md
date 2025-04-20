# Simple Shell Project
A simple Unix command line interpreter built in C.


## Description
This C project is part of the Holberton School and Tuwaiq Academy curriculum.

This project focuses on creating a simple Shell (Unix command line interpreter) using the C programming language.

This Shell reads user commands, executes them, and displays the output — mimics the basic Shell `/bin/sh`.

---

## Features
- Display a prompt and wait for user input.
- Read user input using `getline`.
- Parse the command using `strtok`.
- Execute simple commands using `fork`, `execve`, and `wait`.
- Handle built-in commands:
  - `exit` : Exit the shell.
  - `env`  : Display environment variables.
- Handle command arguments.
- Handle the `PATH` variable to search for commands.
- Handle errors and display error messages.
- Handle End Of File (EOF) with `Ctrl+D`.

---

## Requirements
- Allowed editors: `vi`, `vim`, `emacs`
- Compilation is done on Ubuntu 20.04 LTS using:
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Usage

1. Compile the project:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
```bash
2. Run the shell:
./hsh
```
```bash
3. Example:
$ ./hsh
($) ls
main.c shell.c README.md
($) /bin/pwd
/home/username
($) exit
```

---

## Project Files
| File | Description |
|------|-------------|
| main.c | Main loop of the shell |
| shell.h | Header file with prototypes |
| execute.c | Execute user commands |
| builtin.c | Built-in functions: exit, env |
| path.c | Handle PATH environment variable |
| utils.c | Helper functions |
| AUTHORS | List of project contributors |
| man_1_simple_shell | Manual for using the shell |

---

## Authors
- Haneen Aldawood <https://github.com/hyvuz>
- Munirah Faqihi <https://github.com/MuFaqihi>

---

## Man Page
To read the manual for this shell:
man ./man_1_simple_shell

---
