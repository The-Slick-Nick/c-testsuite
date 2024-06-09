CC = gcc
CFLAGS = -Wall --std=gnu99
LIBDIR = ../lib
INCLDIR = ../include

all: clean rebuild run_test_test clean

$(LIBDIR)/libEWENIT.a:
	make -C ..

rebuild:
	make -C ..

run_test_test: test_test_bin
	./$<

test_test_bin: test_test.o $(LIBDIR)/libEWENIT.a
	$(CC) -o test_test_bin test_test.o -L$(LIBDIR) -l:libEWENIT.a
	# @$(CC) test_test.o ../lib/EWENIT.a -o $@

test_test.o: test_test.c
	$(CC) $(CFLAGS) -c -I$(INCLDIR) $< -o $@

clean:
	@rm -f *.o
	@rm -f *_bin
