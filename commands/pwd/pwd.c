/**
 * @file pwd.c
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de implementação da função que executa o comando pwd
 * 
 * Data de criação: 28/11/2022
 * Datas de modificações: 07/12/022
 */

#include "pwd.h"

char* pwdCommand(StackDirectory* stackDirectory){
  // calcula o tamanho total da saída, sendo que no ext2 o nome pode ser de até 255 caracteres.
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