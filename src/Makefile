CC=g++
CFLAGS=-std=c++11 -c

all: analyze

analyze: analyze.o file.o main.o process.o
	$(CC) analyze.o file.o main.o process.o -o analyze.exe

analyze.o: analyze.cpp
	$(CC) $(CFLAGS) analyze.cpp

file.o: file.cpp
	$(CC) $(CFLAGS) file.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

process.o: process.cpp
	$(CC) $(CFLAGS) process.cpp

clean:
	rm -rf *.o

clean-win:
	del /S *.o
