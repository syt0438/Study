all: main
encrypt.o: encrypt.c
	gcc -c encrypt.c -o encrypt.o
checksum.o: checksum.c
	gcc -c checksum.c -o checksum.o
libsecurity.a: encrypt.o checksum.o
	ar -rcs libsecurity.a encrypt.o checksum.o
main: main.c libsecurity.a
	gcc -I . main.c -L . -l security -o main
clean: 
	rm -rf *.o *.a
