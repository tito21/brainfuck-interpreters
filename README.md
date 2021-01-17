# Brainfuck interpreters

A collection of [brainfuck](https://en.wikipedia.org/wiki/brainfuck)
interpreters in various languages.

# Langues implemented

## C

  - Fixed stack size with no stack overflow
  - Can read from `stdin` or a file
  - Use `make` to compile and `make debug` to compile printing useful
    information for debugging.
  - In the root directory is a slower implementation and under the `c` directory
    is faster. This uses a byte code transcompilation step and a stack layer.
  - Execution time (Mandelbrot) 0m40,974s

## Python

  - Usage:
    `./brainfuck.py filename [-d -s stack_size]`
  - If no stack size is provided a dynamically expanding one is used.
  - `-d` flag toggles printing debug information
  - Can read from `stdin` or a file

## JavaScript

  - Usage: `node brainfuck.js filename`
  - Reads the whole program first creating a "byte code" for execution.
  - Surprisingly fast (6m16,514s)

## GO

  - Usage `go build brainfuck.go` and then `./brainfuck filename`.
  - Very similar to the javascript code.
  - Mandelbrot time 1m48,398s

# Planed

  - ✔Python
  - Lisp
  - Haskell
  - Rust
  - ✔Go

---

# License

All the code is under the [GPLv3 licence](https://www.gnu.org/licenses/)