test: queuetest.c queue.c
	gcc -g -O0 queue.c queuetest.c -o queuetest

brainfuck: brainfuck.c
	gcc brainfuck.c -o brainfuck -O3

debug: brainfuck.c
	gcc brainfuck.c -o brainfuck -DVERBOSE=1

clean:
	rm brainfuck
# target: dependencies
# 	action