# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Paths and files
SRC_DIR = src
SRC = $(SRC_DIR)/main.c
TARGET = shell

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Remove the executable
clean:
	rm -f $(TARGET)

# Convenience
.PHONY: all clean

