CC ?= gcc
CFLAGS = -Wall --std=gnu99
INCLUDE = -I ../EWENIT/
SRC_DIR = ../EWENIT

SRCS = $(wildcard $(SRC_DIR)/*.c)
SRC_OBJS = $(patsubst $(SRC_DIR)/%.c,%.o,$(SRCS))
SRCLIB = $(BIN_DIR)/EWENIT.a

all: run_test_test clean

run_test_test: test_test_bin
	./$<

test_test_bin: test_test.o EWENIT.a
	@$(CC) $^ -o $@

test_test.o: test_test.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@


EWENIT.a: $(SRC_OBJS)
	@ar rvs $@ $^

# For every src .c file, make a .o file
$(SRC_OBJS): %.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@



clean:
	@rm *.o
	@rm *.a
	@rm *_bin
