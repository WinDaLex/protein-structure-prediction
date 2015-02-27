all: train test extract

train: train.c
	gcc -o train.out train.c -lfann -lm

test: test.c
	gcc -o test.out test.c -lfann -lm

extract: extract.c
	gcc -o extract.out extract.c
