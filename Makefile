# Currently a WIP - cobbling some things together now using
# https://github.com/danfis/cu/blob/master/Makefile
# as an example

CC ?= gcc

PREFIX ?= /usr/local
INCLUDEDIR ?= include
LIBDIR ?= lib
BINDIR ?= bin

CFLAGS = -g -Wall

TARGETS = libewenit.a
OBJS = core.o double_assertions.o float_assertions.o int_assertions.o str_assertions.o
HEADERS = EWENIT.h assertion_constants.h float_assertions.h int_assertions.h str_assertions.h

SRC = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRC))


all: $(TARGETS)

libewenit.a: $(OBJS)
	ar cr $@ $^
	ranlib $a

$(OBJS): $(CFILES) $(HEADERS)
	$(CC) $(CFLAGS) -c $@


install: libewenit.a
	mkdir -p $(PREFIX)/$(INCLUDEDIR)
	mkdir -p $(PREFIX)/$(LIBDIR)
	mkdir -p $(PREFIX)/$(BINDIR)
	cp cu.h $(PREFIX)/$(INCLUDEDIR)/
	cp libcu.a $(PREFIX)/$(LIBDIR)/
	cp cu-check-regressions $(PREFIX)/$(BINDIR)/


