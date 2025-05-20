#include "../include/shell.h"

Command commands[] = {
    {"echo", "returns input", "builtin"},
    {"exit", "exits shell", "builtin"},
    {"type", "returns brief description of a command", "builtin"}
};


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
