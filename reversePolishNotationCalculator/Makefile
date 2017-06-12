all : polish
	
polish : main.o stackSource.o
	gcc main.o stackSource.o -o polish

main.o : main.c
	gcc -c main.c

stackSource.o : stackSource.c
	gcc -c stackSource.c

.PHONY:
debug: stackSource.c main.c
	gcc -g main.c stackSource.c -o DEBUG_OUT
	gdb DEBUG_OUT
	rm DEBUG_OUT

.PHONY:
clean:
	rm *.o*

.PHONY:
run: polish
	polish
.PHONY:
mem: polish
	valgrind polish
