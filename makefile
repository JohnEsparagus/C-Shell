CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
SRC = src/main.c src/commands/cmdProcess.c
OUT = shell

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

