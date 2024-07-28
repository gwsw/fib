OBJ = fib.o big.o

CC ?= gcc
CFLAGS = -Wall

fib: $(OBJ)
	$(CC) -o fib $(OBJ)

*.o: big.h

clean:
	rm -f fib *.o
