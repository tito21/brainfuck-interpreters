brainfuck: brainfuck.c queue.c
	gcc brainfuck.c queue.c -o brainfuck -O3

test: queuetest.c queue.c
	gcc -g -O0 queue.c queuetest.c -o queuetest


debug: brainfuck.c queue.c
	gcc -O0 -g queue.c brainfuck.c -o brainfuck -DVERBOSE=1

clean:
	rm brainfuck queue
# target: dependencies
# 	action