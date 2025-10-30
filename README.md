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

## cae-xor
Description
- The cae-xor utility performs encryption and decryption using one or both of the following:
- Caesar cipher: Shifts printable ASCII characters by the values in a key string.
- XOR cipher: Performs bitwise XOR operations with a repeating key.
- The program reads from standard input and writes to standard output, making it compatible with Unix pipelines.

---

Command Line Options:
* -e          Encrypt (default)
* -d          Decrypt
* -c <key>    Caesar cipher key
* -x <key>    XOR cipher key
* -h          Display help message
* -D          Diagnostic output (not implemented)

---
  
Implementation Notes

- Uses read() and write() for direct, unbuffered I/O.
- Restricts Caesar cipher operations to printable ASCII characters (32–126).
- Applies Caesar first, then XOR when encrypting; reverses when decrypting.
- Includes full error checking for arguments and input handling.

---

## mystat
Description

The mystat program is a custom implementation of the Unix stat command. It displays detailed file metadata, including file type, permissions, owner, group, timestamps, and symbolic link targets.

---

Implementation Notes
- Uses lstat() to analyze symbolic links and stat() to test for dangling targets.
- Converts timestamps to both local and UTC using strftime().
- Prints permissions in traditional rwx format.
- All numeric identifiers (inode, UID, GID, etc.) are printed in aligned columns for readability.

---

## Summary
This project demonstrates:
- Low-level C programming with direct system calls.
- String and bitwise manipulation for encryption.
- File metadata extraction with POSIX system calls.
- Modular design with a clean, automated Makefile build process.
- Both utilities are designed for robustness, readability, and compatibility with standard Unix pipelines and workflows.

---

## Build Instructions

Compile all programs:
```bash
make
