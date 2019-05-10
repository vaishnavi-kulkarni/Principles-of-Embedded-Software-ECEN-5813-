CC=gcc
CFLAGS=-I.


project1: ./src/main.o ./src/help.o ./src/allocate.o ./src/display.o ./src/write.o ./src/free.o ./src/invert.o ./src/quit.o ./src/randomizer.o ./src/write_pattern.o ./src/verify_pattern.o
	$(CC) -o project1  ./src/main.o ./src/help.o ./src/allocate.o ./src/display.o ./src/write.o ./src/free.o ./src/invert.o ./src/quit.o ./src/randomizer.o ./src/write_pattern.o ./src/verify_pattern.o

main.o:./src/main.c ./inc/main.h
	$(CC) -c  ./src/main.c
help.o:./src/help.c ./inc/help.h
	$(CC) -c ./src/help.c	    
allocate.o:./src/allocate.c ./inc/allocate.h
	$(CC) -c ./src/allocate.c
display.o:./src/display.c ./inc/display.h
	$(CC) -c ./src/display.c	    	    
write.o:./src/write.c ./inc/write.h
	$(CC) -c ./src/write.c	    
free.o:./src/free.c ./inc/free.h
	$(CC) -c ./src/free.c
invert.o:./src/invert.c ./inc/invert.h
	$(CC) -c ./src/invert.c
quit.o:./src/quit.c ./inc/quit.h
	$(CC) -c ./src/quit.c
write_pattern.o:./src/write_pattern.c ./inc/write_pattern.h
	$(CC) -c ./src/write_pattern.c
verify_pattern.o:./src/verify_pattern.c ./inc/verify_pattern.h
	$(CC) -c ./src/verify_pattern.c
randomizer.o:./src/randomizer.c ./inc/write_pattern.h
	$(CC) -c ./src/randomizer.c
test:  project1 testscript.txt
	./project1 <testscript.txt
clean:
	rm *.o