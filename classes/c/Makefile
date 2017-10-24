
objc = matrix.c rational.c
objh = matrix.h rational.h
objo = matrix.o rational.o

all: $(objo)
	gcc -g3 main.c $(objo) -lm

matrix.o: matrix.c
	gcc -c matrix.c

rational.o: rational.c
	gcc -c rational.c

clear: 
	del *.o
