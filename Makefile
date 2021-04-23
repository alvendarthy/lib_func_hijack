CC=gcc
FLAGS=


run: test fake_malloc.so
	LD_PRELOAD=./fake_malloc.so ./test

test: test.c
	$(CC) test.c -o test

fake_malloc.so: fake_malloc.c
	$(CC) -Wall -fPIC -shared -o fake_malloc.so fake_malloc.c  -ldl


