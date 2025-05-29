#define _POSIX_C_SOURCE 200809L
#include "../../include/shell.h"
const char *processCommand(const char *arg) {
  static char output[MAX_OUTPUT_LEN];
  const char *error = "command not found";
  size_t argLen = strlen(arg);
  
  char *input_copy = strdup(arg); // Make copy of arg cause strtok changes arg
  if (!input_copy) return error;
    
  char *command = strtok(input_copy, " ");
  if (!command) {
    free(input_copy);
    return NULL;
  }
  
  if  (strncmp(arg, "echo ", 5)==0) {
    return executeEcho(arg, argLen);
  }
  else if (strncmp(arg, "type ", 5)==0 && argLen >= 5) {
    return executeType(arg, argLen, output);
  }
  else {
    isInPathExecute(arg, output);
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
	// calcheck if itts a built in
      for (int i = 0; i < COMMAND_COUNT; i++) {
        if (strcmp(secondCommand, commands[i].name)==0) {
          snprintf(output, MAX_OUTPUT_LEN, "%s is a shell of %s", commands[i].name, commands[i].type);
	  return output;
          }
        } 
// check if its in one of PATH directories
    if (isInPath(secondCommand, output)) {
      return output;
    }
    if (argLen + strlen(error) < MAX_OUTPUT_LEN){
       snprintf(output, MAX_OUTPUT_LEN,"%s: %s", secondCommand, error);
       return output;
    }
    return NULL;
}

bool isInPath(const char *command, char output[]) {
     if (!command || !output) {
       return false;
     }
     const char *env_path = getenv("PATH");
     if (!env_path || strlen(env_path) == 0) {
       return false;
     }
     char *path = strdup(env_path);
     if (!path) {
       return false ;
     }
     if (path!=NULL) {
       char *dir = strtok(path,":"); //try to replace wiht your own
       while (dir != NULL) {
         char all_paths[MAX_OUTPUT_LEN];
         snprintf(all_paths, sizeof(all_paths), "%s/%s", dir, command);
           if (access(all_paths, X_OK) == 0){
             strncpy(output, all_paths, MAX_OUTPUT_LEN - 1);
             output[MAX_OUTPUT_LEN - 1] = '\0';
             free(path);
             return true;
           }
         dir = strtok(NULL, ":");
       }
       free(path);
     }
     return false;
}
int isInPathExecute(const char *command, char output[]) {
  char *input_copy = strdup(command); // Make copy of arg cause strtok changes arg
  if (!input_copy) return perror;

  char *first_word = strtok(command, " ");
  if (!first_word) {
    free(input_copy);
    return NULL;
  }

  if (isInPath(first_word, output)) {
    // create an array of the arguments
    char* arguments[ARG_MAX];
    char *token = strtok(command, " ");
    int i = 0;
    while (token!=NULL || i < ARG_MAX) { 
      arguments[i] = token;
      printf("%s", token);
      i++;
      token = strtok(NULL, " ");
    }
    arguments[i+1] = NULL;

    // Now arguemnts is populated with args, and output  with the program 
    int childpid; 
    if ((childpid = fork()) == -1) {
      perror("can't fork");
      exit(1);
    }
    else if (childpid == 0) {
      execv(output, arguments);
      exit(0);
    }
    else {
      printf("finish");
      exit(0);
    }
  }
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
