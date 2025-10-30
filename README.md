# CS333: System Utilities — cae-xor and mystat

## Author
Jeremy Cuthbert  
Portland State University  
CS333 - Jesse Chaney

---

## Project Overview
This project implements two Unix-style command-line utilities written in C:

1. **cae-xor** — a Caesar/XOR encryption and decryption program.
2. **mystat** — a reimplementation of the Unix `stat` command.

Both programs are compiled using the provided Makefile and focus on using system calls (`read`, `write`, `stat`, `lstat`), bitwise operations, and low-level C programming concepts.

---

## Build Instructions

Compile all programs:
```bash
make

## cae-xor
Description

The cae-xor utility performs encryption and decryption using one or both of the following:

Caesar cipher: Shifts printable ASCII characters by the values in a key string.

XOR cipher: Performs bitwise XOR operations with a repeating key.

The program reads from standard input and writes to standard output, making it compatible with Unix pipelines.
