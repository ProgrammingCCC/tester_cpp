CC=g++
CFLAGS=-O2 -WAll -WError -WExtra -I lib/

build: main.o
	$(CC) -o test.out main.o

.PHONY: clean
clean:
	rm *.o && rm *.out


