#! /usr/bin/python3

# Copyright (C) 2019  Alberto Di Biase

import sys

JUMP = 1
CNT = 2
LOOP = 3

class BrainFuckInter():
    def __init__(self, stack_size = 0):
        self.stack_size = stack_size
        self.pointer = 0
        if stack_size == 0:
            self.stack_inf = True
            self.stack = [0]
        else:
            self.stack = [0 for _ in range(stack_size)]
            self.stack_inf = False

        self.inst = {
            '+' : self.inc,
            '-' : self.dec,
            '>' : self.mvr,
            '<' : self.mvl,
            '.' : self.show,
            ',' : self.scan,
            '[' : self.loop_start,
            ']' : self.loop_end
        }

    def resize(self):
        # print(self.pointer, len(self.stack), self.pointer - len(self.stack))
        if self.pointer > len(self.stack)-1:
            self.stack += [0 for _ in range(self.pointer - len(self.stack) + 2)]

    def inc(self):
        if self.stack_inf: self.resize()
        self.stack[self.pointer] += 1
        return CNT

    def dec(self):
        if self.stack_inf: self.resize()
        self.stack[self.pointer] -= 1
        return CNT

    def show(self):
        print("{}".format(chr(self.stack[self.pointer])), end="")
        return CNT

    def scan(self):
        c = input()
        self.stack[self.pointer] = c
        return CNT

    def mvr(self):
        self.pointer+=1
        if self.stack_inf: self.resize()
        return CNT

    def mvl(self):
        self.pointer-=1
        if self.stack_inf: self.resize()
        return CNT

    def loop_start(self):
        if self.stack[self.pointer] == 0:
            return JUMP
        else:
            return CNT

    def loop_end(self):
        return LOOP

    def decode_and_run(self, inst):
        return self.inst[inst]()

    def __repr__(self):
        stack = ""
        for s in self.stack:
            stack += "{:3d}, ".format(s)
        stack = '\n' + str(self.stack) + '\n' \
            + ' ' + "   "*self.pointer  + "^\n" \
            + "Pointer at: {}".format(self.pointer)
        return stack



def getCode(file):
    code = []
    for line in file:
        for c in line:
            if c in "+-<>.,[]":
                code.append(c)
    return code

def matchJump(code, pointer):
    nested = 1
    i = pointer + 1
    while i < len(code):
        if nested == 0:
            return i
        if code[i] == '[':
            nested += 1
        if code[i] == ']':
            nested -= 1
        i += 1
    return i

def matchLoop(code, pointer):
    nested = 1
    i = pointer - 1
    while i > 0:
        if nested == 0:
            return i+1
        if code[i] == '[':
            nested -= 1
        if code[i] == ']':
            nested += 1
        i -= 1
    return 0


if __name__ == "__main__":
    if len(sys.argv) > 1:
        fp = open(sys.argv[1], 'r')
    else:
        fp = sys.stdin
    debug = False
    if "-d" in sys.argv:
        debug = True
    S = 0
    if "-s" in sys.argv:
        S = int(sys.argv[sys.argv.index("-s")+1])

    code = getCode(fp)
    fp.close()
    s = ""
    for c in code:
        s+=c
    print("Executing:")
    print(s)

    bf = BrainFuckInter(stack_size=S)
    i = 0
    while i < len(code):
        if debug: print(code[i], i)
        if debug: print(bf)
        rst = bf.decode_and_run(code[i])
        if rst == JUMP:
            i = matchJump(code, i)
            if debug: print("Match Jump: ", i)
        elif rst == LOOP:
            i = matchLoop(code, i)
            if debug: print("Match Loop: ", i)
        elif rst == CNT:
            i += 1

    print(bf)