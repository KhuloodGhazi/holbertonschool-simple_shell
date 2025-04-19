# hsh - Simple Shell

![C](https://img.shields.io/badge/language-C-00599C?logo=c)

### This Holberton School Low-Level Programming Project (C, Unix)
> A small UNIX command-line interpreter written in ANSI C. hsh supports both interactive and n-interactive modes, executes programs found in the system PATH, and provides a growing set of built-in commands

---

## ✨ Features

| Category            | Details |
|---------------------|---------|
| **Execution**       | Forks a child with `fork()`, replaces image with `execve()`; parent waits with `waitpid()` and propagates exit status |
| **Path resolution** | Searches each directory in `$PATH`; absolute/relative paths exec directly |
| **Built‑ins**   | `exit` → quit shell&nbsp;· `env` → print environment variab |
| **Modes**           | Interactive prompt `:) ` and non‑interactive (stdin) |
| **Error handling**  | Clear messages, proper exit codes (`127` cmd not found, child exit status, etc.) |
| **Memory**          | No leaks – verified with `valgrind --leak-check=full` |

---

## 📑 Requirements

| Requirement                | Value |
|----------------------------|-------|
| **Editors**                | `vi`, `vim`, or `emacs` |
| **Compilation flags**      | `gcc -Wall -Werror -Wextra -pedantic -std=gnu89` *(Ubuntu 20.04 LTS)* |
| **Style**                  | Must follow **Betty** (`betty-style.pl`, `betty-doc.pl`) |
| **Memory**                 | **No leaks** (`valgrind` clean) |
| **Functions per file**     | ≤ 5 |
| **Header guards**          | Every header include‑guarded |
| **System calls**           | Use only when necessary and justify |

---

## 💻 Usage

### Interactive
```console
$ ./hsh
:) ls -l /tmp
total 0
:) exit
$
```
### Non‑interactive
```console
$ echo "/bin/echo Holberton" | ./hsh
Holberton
$
```

---

## 📚 Built‑in Commands

| Command     | Purpose                                  |
|-------------|------------------------------------------|
| `exit`      | Quit shell; returns last command status  |
| `env`       | Print environment variables              |
| `setenv`    | Create / modify an environment variable  |
| `unsetenv`  | Remove an environment variable           |

---

## 🗂️ File Overview

| File               | Purpose                                                     |
|--------------------|-------------------------------------------------------------|
| `main.c`           | Main read‑execute loop, prompt, status tracking             |
| `exec_cmd.c`       | Built‑ins, path resolution, fork/execve, exit‑code logic    |
| `main.h`           | Global prototypes, macros, `extern char **environ`          |
| `man_1_simple_shell` | Manual page (`man ./man_1_simple_shell`)                  |
| `AUTHORS`          | List of contributors                                        |
| `README.md`        | Project documentation (this file)                           |

---

## 🧑‍💻 Authors

* [Abdullah Alameeri](https://github.com/ab10680) – 10680@holbertonstudents.com  
* [Khulood AlOtaibi](https://github.com/KhuloodGhazi) – 10689@holbertonstudents.com  
* [Shahad Aljahdali](https://github.com/shahadFawaz99) – 10707@holbertonstudents.com  

See `AUTHORS` for a full list.
