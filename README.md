# 🐚 Mini Linux Shell (POSIX)

A Unix-like command-line shell implemented in **C** using **POSIX system calls**, built to understand how real shells interact with the Linux kernel.  
This project focuses on **process management, job control, signal handling, and I/O redirection**.

---

## ✨ Features

- Interactive shell prompt with `~` home directory expansion
- Execution of external commands using `fork()` and `execvp()`
- Built-in commands:
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `help`
  - `exit`
- Input redirection (`<`)
- Output redirection (`>`, `>>`)
- Background execution using `&`
- Signal handling:
  - `SIGCHLD` for cleaning up background processes (no zombies)
  - `SIGINT` (Ctrl+C) to terminate foreground commands without exiting the shell
- Modular code structure for parsing, execution, built-ins, and signal handling
- Build system using a Makefile with warnings and debug support

---

## 🧠 Concepts Demonstrated

This project demonstrates hands-on understanding of:

- POSIX process lifecycle (`fork`, `execvp`, `waitpid`)
- File descriptors and I/O redirection (`open`, `dup2`, `close`)
- Signal handling using `sigaction`
- Foreground and background job control
- Command parsing and argument handling
- Modular system-level programming in C

---

## 🛠️ Build & Run

### Build
```bash
make
