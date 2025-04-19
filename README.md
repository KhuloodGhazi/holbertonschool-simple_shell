# hsh - Simple Shell

![C](https://img.shields.io/badge/language-C-00599C?logo=c)
![License: MIT](https://img.shields.io/badge/license-MIT-brightgreen)

> This Holberton School Low-Level Programming Project (C, Unix)
> A small UNIX command-line interpreter written in ANSI C. hsh supports both interactive and n-interactive modes, executes programs found in the system PATH, and provides a growing set of built-in commands

---

## ✨ Features

| Category            | Details |
|---------------------|---------|
| **Execution**       | Forks a child with `fork()`, replaces image with `execve()`; parent waits with `waitpid()` and propagates exit status |
| **Path resolution** | Searches each directory in `$PATH`; absolute/relative paths exec directly |
| **Built‑ins**       | `exit` → quit shell&nbsp;· `env` → print environment variab
| **Modes**           | Interactive prompt `:) ` and non‑interactive (stdin) 
| **Error handling**  | Clear messages, proper exit codes (`127` cmd not found, child exit status, etc.) |

---

## 🔧 Requirements

```bash
gcc -Wall -Wextra -Werror -pedantic -std=gnu89 *.c -o hsh

Project Description:
This project replicates the basic behavior of a UNIX shell.
It reads commands from standard input, pars
===

Features"
- Interactive and non-interactive mode support
- Executes commands with arguments
- Uses the "PATH" environment variable to locate executables
- Built-in "exit" command to terminate the shell
- Handles errors gracefully with informative messages
- Memory management with no leaks

===

Compilation:
The shell is compiled using the following command:
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

===
