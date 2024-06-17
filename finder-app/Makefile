# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS = -lm

# Default target
.DEFAULT_GOAL := writer

#Cross-compilation setup
ifdef CROSS_COMPILE
CC := $(CROSS_COMPILE)gcc
endif

# Source files
SRC = writer.c

# Object files
OBJ = $(SRC:.c=.o)

# Targets
writer: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f writer $(OBJ)
