all: train test extract

train: train.c
	gcc -o train train.c -lfann -lm

test: test.c
	gcc -o test test.c -lfann -lm

extract: extract.c
	gcc -o extract extract.c
