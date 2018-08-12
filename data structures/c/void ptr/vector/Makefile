FILE = test.c
FLAGS = -g3

run: build
	./a.out
debug: build
	gdb a.out
build: vector.o 
	gcc ${FLAGS} ${FILE} vector.o
vector.o: vector.c
	gcc -c vector.c
clear: 
	rm *.o
