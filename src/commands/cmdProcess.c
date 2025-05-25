#define _POSIX_C_SOURCE 200809L
#include "../../include/shell.h"
const char *processCommand(const char *arg) {
  static char output[MAX_OUTPUT_LEN];
  const char *error = "command not found";
  size_t argLen = strlen(arg);
  if  (strncmp(arg, "echo ", 5)==0) {
    return executeEcho(arg, argLen);
  }
  else if (strncmp(arg, "type ", 5)==0 && argLen >= 5) {
    return executeType(arg, argLen, output);
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
  }
  input[strcspn(input, "\n")] = 0;
}

const char *executeEcho(const char *arg, int argLen) {
  
  if (argLen >= 5) {
    return arg+5;
  }
  return "error";
}

const char *executeType(const char *arg, int argLen, char output[]) {
    const char *secondCommand = arg + 5;
    const char *error = "command not found";
    if (!isEmptyOrWhiteSpace(secondCommand)) {
      return error;
    }
// check if itts a built in
      for (int i = 0; i < COMMAND_COUNT; i++) {
        if (strcmp(secondCommand, commands[i].name)==0) {
          snprintf(output, MAX_OUTPUT_LEN, "%s is a shell of %s", commands[i].name, commands[i].type);
	  return output;
          }
        } 
// check if its in one of PATH directories
     char *path = strdup(getenv("PATH"));
     if (path!=NULL) {
       char *dir = strtok(path,":"); //try to replace wiht your own
       while (dir != NULL) {
         char all_paths[MAX_OUTPUT_LEN];
	 snprintf(all_paths, sizeof(all_paths), "%s/%s", dir, secondCommand);
	   if (access(all_paths, X_OK) == 0){
	     strncpy(output, all_paths, MAX_OUTPUT_LEN - 1);
	     output[MAX_OUTPUT_LEN - 1] = '\0';
	     free(path);
	     return output;
	   }
	 dir = strtok(NULL, ":");
       }
       free(path);
     }
     if (argLen + strlen(error) < MAX_OUTPUT_LEN){
       snprintf(output, MAX_OUTPUT_LEN,"%s: %s", secondCommand, error);
       return output;
     }
     return "idk";
}

bool isEmptyOrWhiteSpace(const char *arg) {
  if (arg==NULL) {
    return false;
  }
  while(*arg!='\0'){
    if (!isspace((unsigned char)*arg)) {
      return true; 
    }
    arg++;
  }
  return false;
}
