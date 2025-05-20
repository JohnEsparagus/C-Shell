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

const Command commands[] = {
    {"echo", "returns input", "builtin"},
    {"exit", "exits shell", "builtin"},
    {"type", "returns brief description of a command", "builtin"}
};

