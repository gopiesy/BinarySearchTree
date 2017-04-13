SHELL := /bin/bash

## GCC setup
CC = gcc
CFLAGS += -Wall -Wfatal-errors -fPIC
CFLAGS += -Os

## Targets
TARGET = bstBin
SRC += bst.c
OBJS = $(SRC:.c=.o)

## Build rules
all: $(TARGET) rmbin
$(TARGET): $(OBJS)
	$(CC) $^ $(CFLAGS) -o $@
	

rmbin:
	rm -f *.o

clean:
	rm -f *.o $(TARGET)

.PHONY: all rmbin clean
