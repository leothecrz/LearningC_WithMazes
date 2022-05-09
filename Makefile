
CC=cc

all: main gen run

main: main.o
	$(CC) main.c -o MAIN

mainDebug: main .o
	$(CC) -g main.c MAIN

gen: stack.o gen.o
	$(CC) stack.o gen.o -o GEN

genDebug: stack.o gen.o
	$(CC) -g stack.c gen.c -o GEN  

run: gen main
	$(CC) run.c -o RUN

clean:
	rm *.o MAIN GEN RUN
