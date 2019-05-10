CC=gcc
CFLAGS=-I.
cbuf: ./src/main.o ./src/ring.o
	$(CC) -o cbuf ./src/main.o ./src/ring.o 
test: ./unittest/ring_test.o ./src/ring.o 
	$(CC) -o test ./unittest/ring_test.o ./src/ring.o -lcunit
difftest:  ./src/diffring.o 
	$(CC) -o difftest ./src/diffring.o -lcunit
main.o: ./src/main.c ./inc/ring.h ./inc/main.h
	$(CC) -c ./src/main.c		
ring_test.o: ./unittest/ring_test.c ./inc/ring.h
	$(CC) -c  ./unittest/ring_test.c
ring.o: ./src/ring.c ./inc/ring.h
	$(CC) -c  ./src/ring.c
diffring.o: ./src/diffring.c ./inc/diffring.h
	$(CC) -c  ./src/diffring.c