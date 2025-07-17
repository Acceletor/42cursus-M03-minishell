# Minishell 🐚

A simplified Unix shell built in C as part of the **42 Warsaw** core curriculum.  
Developed in collaboration with [Enes Emre Eravc](https://github.com/enesemreeravci).

## 📚 Project Overview

**Minishell** replicates essential features of a real Unix shell. It handles user input, parses commands, manages processes, supports pipes and redirections, and responds to system signals — all written in pure C without external libraries.

This project strengthened our understanding of:
- Process creation & management (`fork`, `exec`, `wait`)
- Signal handling (`SIGINT`, `SIGQUIT`)
- Pipes and redirection
- Environment variables
- Lexical parsing and tokenization
- Memory management and debugging

## ⚙️ Features

- 🧠 **Custom Lexer & Parser**: Tokenizes and parses complex command inputs  
- 🔁 **Pipes**: Support for commands like `ls -l | grep txt`  
- 🔀 **Redirections**: Input/output redirection (`>`, `<`, `>>`, `<<`)  
- 🧲 **Signal Handling**: Graceful handling of `Ctrl+C` (SIGINT), `Ctrl+\` (SIGQUIT), and `Ctrl+D` (EOF)  
- 🌍 **Environment Support**: Mimics shell variable behavior (`$PATH`, `$?`, etc.)  
- 🧼 **Memory Management**: Fully leak-free (validated with Valgrind)

## 🧪 Example Usage

```shell
$ echo Hello World > file.txt
$ cat < file.txt | grep Hello
Hello World
$ export USERNAME=karintorn
$ echo $USERNAME
karintorn
```

## 🚀 How to Build & Run
> Tested on: macOS and Linux

1. Clone the repository
  ```
  git clone https://github.com/Acceletor/42cursus-M03-minishell.git
  cd 42cursus-M03-minishell
  ```

2. Compile the project
  ```
  make
  ```

3. Run Minishell
```
./minishell
```
4. Exit
```
exit
```

## 🛠️ Tools & Concepts Used
- Language: C
- Build System: Makefile
- System Calls: fork, execve, pipe, dup2, wait, signal
- Debugging: Valgrind
- Norm-compliant: 42 coding style

## 👥 Contributors
- Karintorn (Acceletor)
- Enes Emre Eravc


