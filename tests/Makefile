all: run_test_test clean


run_compile_test: compile_test_bin
	./compile_test_bin

run_test_test: test_test_bin
	./test_test_bin


compile_test_bin: ../bin/EWENIT.a compile_test.o
	gcc compile_test.o ../bin/EWENIT.a -o compile_test_bin

test_test_bin: ../bin/EWENIT.a test_test.o
	gcc test_test.o ../bin/EWENIT.a -o test_test_bin

test_test.o: test_test.c
	gcc -c test_test.c -o test_test.o

compile_test.o: compile_test.c
	gcc -c compile_test.c -o compile_test.o


../bin/EWENIT.a: ../bin/core.o ../bin/int_assertions.o ../bin/str_assertions.o ../bin/float_assertions.o ../bin/double_assertions.o
	ar rvs ../bin/EWENIT.a ../bin/core.o ../bin/int_assertions.o ../bin/str_assertions.o ../bin/float_assertions.o ../bin/double_assertions.o

../bin/core.o: ../EWENIT/core.c
	gcc -c ../EWENIT/core.c -o ../bin/core.o

../bin/int_assertions.o: ../EWENIT/int_assertions.c
	gcc -c ../EWENIT/int_assertions.c -o ../bin/int_assertions.o

../bin/str_assertions.o: ../EWENIT/str_assertions.c
	gcc -c ../EWENIT/str_assertions.c -o ../bin/str_assertions.o

../bin/float_assertions.o: ../EWENIT/float_assertions.c
	gcc -c ../EWENIT/float_assertions.c -o ../bin/float_assertions.o

../bin/double_assertions.o: ../EWENIT/double_assertions.c
	gcc -c ../EWENIT/double_assertions.c -o  ../bin/double_assertions.o

clean:
	@rm *.o
	@rm *_bin
	@rm ../bin/*.o

