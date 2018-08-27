all: tromino.out

tromino.out: 
		gcc -std=c11 tromino.c -lm -o tromino.out

clean:
	rm -f tromino.out
