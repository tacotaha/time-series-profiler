CC=gcc
CFLAGS=-Wall -Werror -std=c99 -pedantic
EXEC=profile

all: profiler 

profiler: main.o profiler.o
	$(CC) main.o profiler.o -o profile

main.o: Main.c
	$(CC) -c Main.c -o main.o

profiler.o: Profiler.c Profiler.h
	$(CC) -c Profiler.c -o profiler.o

clean:
	\rm -f $(EXEC) *.o *~
