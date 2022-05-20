
@enum Signal PNT JMP BRZ INC DCN INC_TP DCN_TP

mutable struct Instruction
    inst::Signal
    next_pc::Int
end

function readProgram(code::Vector{UInt8})
    program = ""
    for c ∈ code
        c = Char(c)
        if c in ['>', '<', '+', '-', '[', ']', '.']
            program = string(program, "$c")
        end
    end
    return program
end

function getBytecode(program::String)
    loop_stack::Vector{Int} = []
    code::Vector{Instruction} = []
    for (i, c) ∈ enumerate(program)
        if c == '>'
            push!(code, Instruction(INC_TP, -1))
        elseif c == '<'
            push!(code, Instruction(DCN_TP, -1))
        elseif c == '+'
            push!(code, Instruction(INC, -1))
        elseif c == '-'
            push!(code, Instruction(DCN, -1))
        elseif c == '.'
            push!(code, Instruction(PNT, -1))
        elseif c == '[' # open loop
            push!(code, Instruction(BRZ, -1))
            # println("BRZ at $i")
            pushfirst!(loop_stack, i)
        elseif c == ']' # close loop (jmp back)
            s = popfirst!(loop_stack)
            code[s].next_pc = i + 1
            push!(code, Instruction(JMP, s))
        end
        # println(loop_stack)
    end
    code
end

function runCode(code::Vector{Instruction})
    p::Int = 1
    inst_pointer::Int = 1
    tape = zeros(UInt8, 2)
    len_code = length(code)
    while inst_pointer < len_code
        inst = code[inst_pointer]
        if inst.inst == INC
            tape[p] += 0x01
            inst_pointer += 1
        elseif inst.inst == DCN
            tape[p] -= 0x01
            inst_pointer += 1
        elseif inst.inst == INC_TP
            p += 1
            if length(tape) < p
                push!(tape, 0x00)
            end
            inst_pointer += 1
        elseif inst.inst == DCN_TP
            p -= 1
            inst_pointer += 1
        elseif inst.inst == JMP
            inst_pointer = inst.next_pc
        elseif inst.inst == BRZ
            if tape[p] == 0x00
                inst_pointer = inst.next_pc
            else
                inst_pointer += 1
            end
        elseif inst.inst == PNT
            # println("tape at $p: $(tape[p])")
            print(String([tape[p]]))
            inst_pointer += 1
        end
    end
    tape, p
end

function main()

    raw_code = ""
    open(ARGS[1], "r") do io
        raw_code = read(io)
    end
    program = readProgram(raw_code)
    println(length(program))
    code = getBytecode(program)
    println(length(code))
    # println(code)
    tape, p = runCode(code)
    println("\n")
    println(p)
    println(tape[p-2:p+2])
end

main()