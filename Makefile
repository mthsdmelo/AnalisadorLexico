
all : compilar

compilar : lexico.c
	gcc -g lexico.c -o compilador -lm -Wall

.PHONY:clean

clean:
	-rm -f *.o
