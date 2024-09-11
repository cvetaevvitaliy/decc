# Makefile for Data Error Checking and Correction project

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
DEPS = decc_code.h
OBJ = decc_code.o main.o
EXEC = decc_test_program

# Default target
all: $(EXEC)

# Build executable
$(EXEC): $(OBJ)
	$(CC) -o $@ $^

# Compile source files into object files
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean up build files
clean:
	rm -f *.o $(EXEC)
