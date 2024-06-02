CC ?= gcc
CFLAGS = -Wall --std=gnu99
INCLUDE = -I ../src/


all: build_lib run_test_test clean

build_lib:
	make -C ..

run_test_test: test_test_bin
	./$<

test_test_bin: test_test.o ../bin/EWENIT.a
	@$(CC) $^ -o $@

test_test.o: test_test.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm *.o
	@rm *_bin
