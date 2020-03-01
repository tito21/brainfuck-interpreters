# Brainfuck interpreters

A collection of [brainfuck](https://en.wikipedia.org/wiki/brainfuck)
interpreters in various languages.

# Langues implemented

## C

  - Fixed stack size with no stack overflow
  - Can read from `stdin` or a file
  - Use `make` to compile and `make debug` to compile printing useful
    information for debugging.

## Python

  - Usage:
    `./brainfuck.py filename [-d -s stack_size]`
  - If no stack size is provided a dynamically expanding one is used.
  - `-d` flag toggles printing debug information
  - Can read from `stdin` or a file

## JavaScript

  - Usage: `node brainfuck.js filename`
  - Reads the whole program first creating a "byte code" for execution.
  - Surprisingly fast

# Planed

  - ✔Python
  - Lisp
  - Haskell
  - Rust
  - Go

---

# License

All the code is under the [GPLv3 licence](https://www.gnu.org/licenses/)