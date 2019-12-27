brainfuck: brainfuck.c
	gcc brainfuck.c -o brainfuck

debug: brainfuck.c
	gcc brainfuck.c -o brainfuck -DVERBOSE=1

clean:
	rm brainfuck
# target: dependencies
# 	action