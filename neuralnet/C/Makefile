all: train.out test.out extract.out

train.out: train.c
	gcc -o train.out train.c -lfann -lm

test.out: test.c
	gcc -o test.out test.c -lfann -lm

extract.out: extract.c
	gcc -o extract.out extract.c
