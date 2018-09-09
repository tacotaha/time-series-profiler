CC=gcc
CFLAGS=-Wall -Werror -std=c99 -pedantic
EXEC=profile memhog
OBJ=main.o meminfo.o memhog.o
all: profiler memhog 

profiler: main.o meminfo.o
	$(CC) main.o meminfo.o -o profile

memhog: meminfo.o memhog.o
	$(CC) meminfo.o memhog.o -o memhog

main.o: src/Main.c
	$(CC) -c src/Main.c -o main.o

meminfo.o: src/Meminfo.c src/Meminfo.h
	$(CC) -c src/Meminfo.c -o meminfo.o

memhog.o: tests/MemHog.c
	$(CC) -c tests/MemHog.c -o memhog.o

clean:
	\rm -f $(EXEC) $(OBJ) *~
