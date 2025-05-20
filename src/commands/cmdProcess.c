#include "../../include/shell.h"
const char *processCommand(const char *arg) {
  static char* output[MAX_OUTPUT_LEN];
  const char *error = "command not found";
  size_t argLen = strlen(arg);
  if  (strncmp(arg, "echo ", 5)==0 && argLen >= 5) {
    return arg + 5;
  }
  else if (strncmp(arg, "type ", 5)==0 && argLen >= 5) {
    const char *secondCommand = arg + 5;

      for (int i = 0; i < COMMAND_COUNT; i++) {
        if (strcmp(secondCommand, commands[i].name)==0) {
          int n = snprintf(output, MAX_OUTPUT_LEN, "%s is a shell of %s", commands[i].name, commands[i].type);
          return output;
          }
        }
     if (argLen + strlen(error) < MAX_OUTPUT_LEN){
       snprintf(output, MAX_OUTPUT_LEN,"%s: %s", secondCommand, error);
       return output;
     }
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

