# gcc -fPIC 选项：用于创建位置无关代码，有的操作系统和处理器要用位置无关代码创建库，这样它们才能在运行时决定把代码加载到存储器的哪个位置
# 在类 Unix 系统中，编译器只会记录动态库的文件名，而不会包含路径名。也就是说如果不把动态库保存到标准目录，程序就找不到它。为了解决这个问题，Linux会检查保存在 LD_LIBRARY_PATH 变量中的附加目录，只要把库目录添加到 LD_LIBRARY_PATH 中，并export它， 程序就能找到动态库
all: main
encrypt.o: encrypt.c
	gcc -I . -c encrypt.c -o encrypt.o
checksum.o: checksum.c
	gcc -I . -c checksum.c -o checksum.o
libsecurity.so: encrypt.o checksum.o
	gcc -shared encrypt.o checksum.o -o /lib64/libsecurity.so
main: main.c libsecurity.so
	gcc -I . main.c -l security -o main
clean: 
	rm -f encrypt.o checksum.o /lib64/libsecurity.so main
