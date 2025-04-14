# Simple Shell - "hsh"
A simple UNIX command-line interpreter written in C, as part of the Holberton School Low-Level Programming curriculum.

===

Project Description:
This project replicates the basic behavior of a UNIX shell.
It reads commands from standard input, parses them, and executes them using system calls such as "fork", "execve", and "wait".

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

Usage:
---- Interactive mode
./hsh
($) ls -l
($) exit
---- Non-interactive mode
./hsh
($) ls -l
($) exit

===

Learning Objectives:
- How a shell works internally
- Process creation using fork and execution with execve
- Use of PATH and environment variables
- Parsing user input and tokenizing commands
- Memory handling and avoiding leaks
- Writing portable and maintainable C code

===

Authors:
- Abdullah Alameeri
- Khulood Alotaibi
- Shahad Aljahdali
See the full contributors in the AUTHORS file.


===

Man Page:
Run man ./man_1_simple_shell for usage documentation.