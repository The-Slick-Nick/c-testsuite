CC ?= gcc

# This-project relative paths
LIB ?= ./lib
INCL ?= ./include

# User file system
PREFIX     ?= /usr/local
INCLUDEDIR ?= include
LIBDIR     ?= lib


# File identification
TARGET ?= $(LIB)/libEWENIT.a

SOURCES ?= $(wildcard ./src/*.c)
HEADERS ?= $(wildcard ./src/*.h)
SRC_OBJS = $(patsubst ./src/%.c, %.o, $(SOURCES))

all: move build clean

# To put libraries & such on in user home
install: $(TARGET)
	mkdir -p $(PREFIX)/$(INCLUDEDIR)
	mkdir -p $(PREFIX)/$(LIBDIR)
	mkdir -p $(PREFIX)/$(BINDIR)

	cp $(HEADERS) $(PREFIX)/$(INCLUDEDIR)
	cp $(TARGET) $(PREFIX)/$(LIBDIR)


move: $(LIB) $(INCL)
	@cp $(HEADERS) $(INCL)

build: $(TARGET)

clean:
	@rm -f *.o

$(TARGET): $(SRC_OBJS)
	@ar rvs $@ $^

$(SRC_OBJS): %.o: ./src/%.c
	@$(CC) $(CFLAGS) -I $(INCL) -c $< -o $@


$(LIB):
	@mkdir -p $@

$(INCL):
	@mkdir -p $@


