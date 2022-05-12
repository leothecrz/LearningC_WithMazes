 
CC=gcc
Flags=-lstdc++

Default: main debug

clean:
	@rm *.o MAIN DEBUG

main: main.o gen.o stack.o solve.o
	$(CC) main.o gen.o stack.o solve.o $(Flags) -o MAIN

debug: 
	$(CC) main.cpp gen.cpp stack.cpp solve.cpp $(Flags) -g -o DEBUG
	 

