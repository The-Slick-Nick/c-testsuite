CC ?= gcc
CFLAGS = -Wall --std=gnu99

OBJS = test_test.o ../bin/EWENIT.a
EWENIT_LIB = ../bin/EWENIT.a
EWENIT_OBJS = ../bin/core.o ../bin/int_assertions.o ../bin/str_assertions.o ../bin/float_assertions.o ../bin/double_assertions.o

all: run_test_test clean


run_test_test: test_test_bin
	./test_test_bin

run_readme_example: readme_example_bin
	./readme_example_bin

test_test_bin: $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o test_test_bin

readme_example_bin: readme_example.o $(EWENIT_LIB)
	@$(CC) $(CFLAGS) readme_example.o $(EWENIT_LIB) -o readme_example_bin

test_test.o: test_test.c
	@$(CC) $(CFLAGS) -c test_test.c -o test_test.o

readme_example.o: readme_example.c
	@$(CC) $(CFLAGS) -c readme_example.c -o readme_example.o


$(EWENIT_LIB): $(EWENIT_OBJS)
	@ar rvs $(EWENIT_LIB) $(EWENIT_OBJS)

../bin/core.o: ../EWENIT/core.c
	@gcc -Wall -c ../EWENIT/core.c -o ../bin/core.o

../bin/int_assertions.o: ../EWENIT/int_assertions.c
	@gcc -Wall -c ../EWENIT/int_assertions.c -o ../bin/int_assertions.o

../bin/str_assertions.o: ../EWENIT/str_assertions.c
	@gcc -Wall -c ../EWENIT/str_assertions.c -o ../bin/str_assertions.o

../bin/float_assertions.o: ../EWENIT/float_assertions.c
	@gcc -Wall -c ../EWENIT/float_assertions.c -o ../bin/float_assertions.o

../bin/double_assertions.o: ../EWENIT/double_assertions.c
	@gcc -Wall -c ../EWENIT/double_assertions.c -o  ../bin/double_assertions.o

clean:
	@rm *.o
	@rm *_bin
	@rm ../bin/*.o

