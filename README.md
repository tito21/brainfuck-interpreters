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

## Julia

  - Usage `julia brainfuck.jl filename`
  - Uses a transcomilation step similar to the javascript implementation
  - Mandelbrot time 0m54,092s, after some optimization does deliver. I might
  start using it for my own programs

## Rust
  - Usage `rustc brainfuck.rs -C opt-level=3` and then `./brainfuck filename`.
  - As usal uses a transcompilation step similar to the other implementations.
  - Mandelbrot time 0m34,147s

# Planed

  - ✔Python
  - Lisp
  - Haskell
  - ✔Rust
  - ✔Go

---

# License

All the code is under the [GPLv3 licence](https://www.gnu.org/licenses/)