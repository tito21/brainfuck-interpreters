// Copyright (C) 2020  Alberto Di Biase

class Instruction {
    constructor(inst, jmp_pos) {
        this.inst = inst;
        this.jmp_pos = jmp_pos;
    }

}

class BFMachine {
    constructor(prog) {
        this.prog = prog.match(/[\+\-\[\]<>\.]/g);
        // console.log(this.prog);
        this.byte_codes = [];
        this.tape = [0];
        this.pc = 0;
        this.pointer = 0;
        this.transcompile();
        console.log(this.byte_codes);
    }

    exec_inst(byte_inst) {
        switch (byte_inst.inst) {
            case '>':
                this.pointer += 1
                if (this.tape.length < this.pointer + 1) {
                    this.tape.push(0)
                }
                this.pc += 1;
                break;
            case '<':
                this.pointer -= 1;
                this.pc += 1;
                break;
            case '+':
                this.tape[this.pointer] += 1;
                this.pc += 1;
                break;
            case '-':
                this.tape[this.pointer] -= 1;
                this.pc += 1;
                break;
            case '[':
                if (this.tape[this.pointer] == 0) {
                    this.pc = byte_inst.jmp_pos;
                }
                else {
                    this.pc += 1;
                }
                break;
            case ']':
                this.pc = byte_inst.jmp_pos;
                break;
            case '.':
                let s = this.tape[this.pointer];
                if (CHAR) {
                    s = String.fromCodePoint(this.tape[this.pointer]);
                }
                process.stdout.write(s);
                this.pc += 1;
                break;
            default:
                throw Error("Invalid instruction: " + inst)
        }
    }

    transcompile() {
        let loop_start = [];
        for (let i=0; i < this.prog.length; i++) {
            const inst = this.prog[i];
            let b_inst = new Instruction(inst);
            // console.log(i, b_inst, loop_start);
            if (inst == '[') {
                loop_start.unshift({'pos': i, 'inst': b_inst});
            }
            else if (inst == ']') {
                let s = loop_start.shift();
                b_inst.jmp_pos = s.pos
                s.inst.jmp_pos = i+1;
            }
            this.byte_codes.push(b_inst);
        }
    }

    step() {
        if (this.pc > this.byte_codes.length - 1) {
            return 0;
        }
        this.exec_inst(this.byte_codes[this.pc]);
        return 1;
    }

}


const CHAR = true;
const DEBUG = false;

const fs = require('fs');
const process = require('process');

let prog;
if (process.argv.length > 2) {
    let fname = process.argv[2];
    console.log(fname);
    prog = fs.readFileSync(fname, {encoding: 'utf-8'});
}
else {
    console.log("No file provided");
    throw Error;
}

let machine = new BFMachine(prog);

let i = 0;
let code = 1;
while (code) {
    code = machine.step();
    if (DEBUG) {
        console.log("--------------------")
        console.log("Step", i++);
        console.log("Current inst:", machine.byte_codes[machine.pc]);
        console.log("Value at the pointer", machine.tape[machine.pointer]);
        console.log("Pointer:", machine.pointer);
        console.log("tape:", machine.tape);
        console.log("pc:", machine.pc);
    }
}

console.log("\n-------------------- End of program --------------------\n");
console.log(machine.tape);
console.log(machine.pointer);
