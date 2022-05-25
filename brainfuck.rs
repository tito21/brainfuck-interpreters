use std::num::Wrapping;
use std::fs;
use std::env;

#[allow(non_camel_case_types)]
#[derive(PartialEq)]
#[derive(Debug)]
enum Signal {
    PNT,
    JMP,
    BRZ,
    INC_TP,
    INC,
    DCN,
    DCN_TP,
    NOP
}

#[derive(Debug)]
struct Instruction {
    inst: Signal,
    next_pc: usize
}


fn get_bytecode(program: &str) -> Vec<Instruction> {
    let mut code = Vec::<Instruction>::with_capacity(program.len());
    let mut stack = Vec::<usize>::new();
    for (i, p) in program.chars().enumerate() {
        // println!("{} {}", i, p);
        let mut byte_inst:Instruction = Instruction {inst: Signal::NOP, next_pc: 0};
        if p == '+' {
            byte_inst = Instruction {inst: Signal::INC, next_pc: 0};
        }
        else if p == '-' {
            byte_inst = Instruction {inst: Signal::DCN, next_pc: 0};
        }
        else if p == '>' {
            byte_inst = Instruction {inst: Signal::INC_TP, next_pc: 0};
        }
        else if p == '<' {
            byte_inst = Instruction {inst: Signal::DCN_TP, next_pc: 0};
        }
        else if p == '.' {
            byte_inst = Instruction {inst: Signal::PNT, next_pc: 0};
        }
        else if p == '[' {
            byte_inst = Instruction {inst: Signal::BRZ, next_pc: 0};
            stack.push(i);
        }
        else if p == ']' {
            let s = stack.pop().unwrap();
            code[s].next_pc = i+1;
            byte_inst = Instruction {inst: Signal::JMP, next_pc: s};
        }
        code.push(byte_inst);
    }
    return code
}

fn run_code(code: &Vec<Instruction>) {
    let mut pointer = 0usize;
    let mut tape = vec![Wrapping(0u8), Wrapping(0u8)];
    let mut inst_pointer = 0usize;
    while inst_pointer < code.len() {
        let inst = &code[inst_pointer];
        if inst.inst == Signal::INC {
            inst_pointer += 1;
            tape[pointer] += 1;
        }
        else if inst.inst ==  Signal::DCN {
            inst_pointer += 1;
            tape[pointer] -= 1;
        }
        else if inst.inst ==  Signal::INC_TP {
            inst_pointer += 1;
            pointer += 1;
            if tape.len() > pointer {
                tape.push(Wrapping(0u8));
            }
        }
        else if inst.inst ==  Signal::DCN_TP {
            inst_pointer += 1;
            pointer -= 1;
        }
        else if inst.inst ==  Signal::BRZ {
            if tape[pointer] == Wrapping(0u8) {
                inst_pointer = inst.next_pc;
            }
            else {
                inst_pointer += 1;
            }
        }
        else if inst.inst ==  Signal::JMP {
                inst_pointer = inst.next_pc;
        }
        else if inst.inst ==  Signal::PNT {
                print!("{}", tape[pointer].0 as char);
                inst_pointer += 1;
        }
        else if inst.inst ==  Signal::NOP {
            inst_pointer += 1;
        }
    }

}


fn main() {
    let args: Vec<String> = env::args().collect();

    // println!("{:?}", args);

    let program = fs::read_to_string(&args[1])
        .expect("Something went wrong reading the file");
    // println!("{}", program);

    let code = get_bytecode(&program);
    // println!("{:?}", code);
    run_code(&code);

}