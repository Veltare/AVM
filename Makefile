CC=g++

CFLAGS=-c -Wall

all: main

main: SB.o ASM.o GUI.o
	$(CC) SB.o ASM.o GUI.o -o main

SB.o: SB.cpp
	$(CC) $(CFLAGS) ./cursProject/SimpleBasic/SB.cpp

ASM.o: ASM.cpp
	$(CC) $(CFLAGS) ./cursProject/SimpleAssembler/ASM.cpp

GUI.o: GUI.cpp
	$(CC) $(CFLAGS) ./MySimpleComputer/GUI/GUI.cpp

clean:
	rm -rf *.o main


