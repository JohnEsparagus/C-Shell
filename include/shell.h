#ifndef SHELL_H
#define SHELL_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COMMAND_COUNT 3
#define MAX_INPUT_LEN 100
#define MAX_OUTPUT_LEN 256

typedef struct {
    const char *name;
    const char *description;
    const char *type;
} Command;

extern Command commands[];

const char *processCommand(const char *arg);
void printPrompt(void);
void readInput(char *input, size_t size);

#endif 
