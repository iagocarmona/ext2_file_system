#include "pwd.h"

char* pwdCommand(StackDirectory* stackDirectory){
  int size = (255 * stackDirectory->qtdDirectory) + stackDirectory->qtdDirectory;
  char* output = (char*)calloc(size + 1, sizeof(char));

  NodeStackDirectory* aux = stackDirectory->rootDirectory;

  for (int i = 0; i < stackDirectory->qtdDirectory; i++) {
    strcat(output, aux->name);
    if ((i + 1) != stackDirectory->qtdDirectory) {
      if (i) strcat(output, "/");
      aux = aux->next;
    }
  }
  return output;
}