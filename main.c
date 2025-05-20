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

bool isValidCommand(const char *arg){}
const char *process_command(const char *arg);
void print_prompt(void);
void read_input(char *input, size_t size);


int main(int argc, char  *argv[]) {}

bool isValidCommand(const char *arg) {
  for (int i = 0; i < COMMAND_COUNT; i++) {
    if (strcmp(arg, commands[i].name)==0) {
      return true;
    }
  }
  return false;  
}

const char *process_command(const char *arg) {}

void print_prompt(void) {
  printf("$ ");
}

void read_input(char *input, size_t size) {}

