main.o: main.c
	gcc -c main.c
test.o: test.c test.h
	gcc -c test.c test.h
demo: main.o test.o
	gcc *.o -o demo
