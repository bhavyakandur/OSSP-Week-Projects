# ShellForge - Cloud Administration Shell

## OSSP Week 1 Project

ShellForge is a simple Linux command-line shell developed as part of the
Operating Systems and System Programming (OSSP) course.

The project demonstrates important operating-system concepts such as
process creation, process execution, inter-process communication,
file descriptors, input/output redirection, and process synchronization.

---

## Objective

The objective of ShellForge is to understand how a command-line shell
works internally and how Linux creates and manages processes.

The shell accepts commands from the user, creates child processes when
required, executes Linux programs, waits for processes, and supports
basic shell features.

---

## Features

- Interactive shell prompt
- Command input handling
- `exit` command
- Linux command execution using `execvp()`
- Process creation using `fork()`
- Process synchronization using `waitpid()`
- Directory changing using `chdir()`
- Current directory using `getcwd()`
- Command arguments
- Output redirection using `>`
- Append output redirection using `>>`
- Input redirection using `<`
- Pipe communication using `|`
- Background command execution using `&`
- Basic error handling

---

## Technologies Used

- C Programming Language
- Linux / Ubuntu
- GCC Compiler
- POSIX System Calls
- Git and GitHub

---

## OS Concepts Demonstrated

### Process Creation

`fork()` creates a new child process.

### Program Execution

`execvp()` replaces the child process with the requested Linux command.

### Process Synchronization

`waitpid()` allows the shell to wait for foreground processes.

### Directory Management

`chdir()` changes the current working directory.

### File Descriptors

`open()`, `close()`, and `dup2()` are used for file redirection.

### Inter-Process Communication

`pipe()` connects the output of one process to the input of another.

---

## Project Structure

```text
OSSP-PBL/
│
├── Makefile
├── README.md
│
├── bin/
│   └── shellforge
│
├── docs/
│
├── include/
│   └── shell.h
│
├── screenshots/
│
├── src/
│   ├── main.c
│   ├── execute.c
│   └── builtin.c
│
└── tests/

## Week 2 Features

- Dynamic command input
- Memory allocation using malloc()
- Automatic buffer expansion using realloc()
- Proper memory cleanup using free()## Week 2 Features

- Dynamic command input
- Memory allocation using malloc()
- Automatic buffer expansion using realloc()
- Proper memory cleanup using free()

## Week 3 Features

- Command parsing using strtok()
- Dynamic argv[] construction
- Modular parser implementation
- Ready for process execution with execvp()

## Week 4 Features

- Process creation using fork()
- Command execution using execvp()
- Parent-child synchronization using waitpid()
- Error handling using perror()

## Week 5 Features

- Built-in command support
- cd
- pwd
- help
- clear
- exit
- Environment variables

## Week 6 Features

- Signal handling
- SIGINT support
- SIGCHLD support
- Zombie cleanup
- Shell survives Ctrl+C


