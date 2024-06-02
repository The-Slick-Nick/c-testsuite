CC ?= gcc

BIN ?= ./bin
INCL ?= ./include

TARGET ?= ./bin/EWENIT.a

SOURCES ?= $(wildcard ./src/*.c)
HEADERS ?= $(wildcard ./src/*.h)
SRC_OBJS = $(patsubst ./src/%.c, %.o, $(SOURCES))

all: move build clean

move: $(BIN) $(INCL)
	@cp $(HEADERS) $(INCL)

build: $(TARGET)

clean:
	@rm -f *.o

$(TARGET): $(SRC_OBJS)
	@ar rvs $@ $^

$(SRC_OBJS): %.o: ./src/%.c
	@$(CC) $(CFLAGS) -I $(INCL) -c $< -o $@


$(BIN):
	@mkdir -p $@

$(INCL):
	@mkdir -p $@

