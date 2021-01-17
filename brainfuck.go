package main

import (
    "fmt"
    "io/ioutil"
    "strings"
    "os"
)

func check(e error) {
    if e != nil {
        panic(e)
    }
}


var tape [3200]uint8
var pointer, pos int

type Instruction struct {
    action byte
    jump int
}

var code []Instruction

func printInstructions(inst []Instruction) {
    fmt.Print("[ ")
    for i:=0; i < len(inst); i++ {
        fmt.Printf("{%c, %v}, ", inst[i].action, inst[i].jump)
    }
    fmt.Print("]\n")
}


func getByteCode(prog string) []Instruction {
    var instructions []Instruction
    var stack []int
    var code string
    for i := 0; i < len(prog); i++ {
        if strings.Contains("+-><[].,", string(prog[i])) {
            code = code + string(prog[i])
        }
    }
    prog = code
    for i := 0; i < len(prog); i++ {
        // fmt.Println(prog[i])
        inst := Instruction{action: prog[i], jump: -1}
        instructions = append(instructions, inst)
        if prog[i] == '[' {
            stack = append(stack, i)
            instructions[i].jump = i
        } else if prog[i] == ']' {
            instructions[i].jump = stack[len(stack)-1]
            instructions[stack[len(stack)-1]].jump = i
            stack = stack[:len(stack)-1]
        }

    }
    return instructions
}

func executeInst(inst Instruction) bool {
// This function has side effects. It changes global var `tape`, `pointer` and `pos`
    switch inst.action {
    case '+':
        tape[pointer]++
        pos++
    case '-':
        tape[pointer]--
        pos++
    case '>':
        pointer++
        pos++
    case '<':
        pointer--
        pos++
    case '[':
        if tape[pointer] == 0 {
            pos = inst.jump + 1
        } else {
            pos++
        }
    case ']':
        pos = inst.jump
    case '.':
        pos++
        fmt.Printf("%c", tape[pointer])
    }

    if pos > len(code) - 1 {
        return false
    } else {
        return true
    }
}

func readfile(path string) string {
    dat, err := ioutil.ReadFile(path)
    check(err)
    data := string(dat)
    return data
}

func main() {
    fname := os.Args[1]
    prog := readfile(fname)
    code = getByteCode(prog)
    // printInstructions(code)
    cont := true
    for cont {
        cont = executeInst(code[pos])
        // fmt.Println(tape)
        // fmt.Println(pointer)
    }

}
