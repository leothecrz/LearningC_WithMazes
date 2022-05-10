
CC=cc

all: main gen run edit

main: main.o
	$(CC) main.c -o MAIN

mainDebug: main .o
	$(CC) -g main.c MAIN

gen: gen.o
	$(CC) gen.o -o GEN

genDebug: gen.o
	$(CC) -g gen.c -o GEN  

edit: edit.o
	$(CC) edit.c -o EDIT

run: run.o gen main
	$(CC) run.c -o RUN

clean:
	rm *.o MAIN GEN RUN EDIT
