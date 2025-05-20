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

//bool isValidCommand(const char *arg){}
const char *processCommand(const char *arg);
void printPrompt(void);
void readInput(char *input, size_t size);


int main(int argc, char  *argv[]) {
  setbuf(stdout,NULL);
  char  input[MAX_INPUT_LEN];
  while (1) {
    printPrompt();
    readInput(input, sizeof(input));

    if (strcmp(input, "exit")==0) {
      return EXIT_SUCCESS;
    }
    const char *output = processCommand(input);
    if (output) {
      printf("%s\n", output);
    }
  }
}
/*
bool isValidCommand(const char *arg) {
  for (int i = 0; i < COMMAND_COUNT; i++) {
    if (strcmp(arg, commands[i].name)==0) {
      return true;
    }
  }
  return false;  
}
*/
const char *processCommand(const char *arg) {
  static char* output[MAX_OUTPUT_LEN];
  const char *error = " : command not found";
  
  if  (strncmp(arg, "echo ", 5)==0) {
    return arg + 5;
  }
  else if (strncmp(arg, "type ", 5)==0) {
    const char *secondCommand = arg + 5;
    
      for (int i = 0; i < COMMAND_COUNT; i++) {
        if (strcmp(secondCommand, commands[i].name)==0) {
          int n = snprintf(output, MAX_OUTPUT_LEN, "%s is a shell of %s", commands[i].name, commands[i].type);
	  return output;
	  }  
        }
     strcat(arg+5,error);
     return arg+5;
     }
  else {
    printf("%s: %s\n", arg, error);	  
  }
  return NULL;
}

void printPrompt(void) {
  printf("$ ");
}

void readInput(char *input, size_t size) {
  if (fgets(input, size, stdin)==NULL) {
    strcpy(input, "exit");
    return;
  }
  input[strcspn(input, "\n")] = 0; 
}
