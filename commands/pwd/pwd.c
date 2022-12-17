/**
 * @file pwd.c
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de implementação da função que executa o comando pwd
 * @version 0.1
 * @date 2022-12-17
 * 
 * 
 */

#include "pwd.h"

char* pwdCommand(StackDirectory* stackDirectory){
  int size = (255 * stackDirectory->qtdDirectory) + stackDirectory->qtdDirectory;
  char* output = (char*)calloc(size + 1, sizeof(char));

  NodeStackDirectory* aux = stackDirectory->rootDirectory; /* pega o diretório raiz */

  for (int i = 0; i < stackDirectory->qtdDirectory; i++) {
    strcat(output, aux->name); /* anexa em output o nome */
    if ((i + 1) != stackDirectory->qtdDirectory) {
      if (i) strcat(output, "/"); /* anexa '/' em output */
      aux = aux->next; /* aponta para o próximo */
    }
  }
  return output;
}