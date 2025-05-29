#ifndef SHELL_H
#define SHELL_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#define COMMAND_COUNT 3
#define MAX_INPUT_LEN 100
#define MAX_OUTPUT_LEN 256
#define ARG_MAX 1000
typedef struct {
    const char *name;
    const char *description;
    const char *type;
} Command;

extern Command commands[];

const char *processCommand(const char *arg);
void printPrompt(void);
void readInput(char *input, size_t size);
const char *executeEcho(const char *arg, int argLen);
const char *executeType(const char *arg, int argLen, char output[]);
bool isEmptyOrWhiteSpace(const char *arg);
bool isInPath(const char *command, char output[]);
int isInPathExecute(const char *command, char output[]);
#endif 
