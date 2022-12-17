/**
 * @file stackDirectory.c
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de implementação das funções de manipulação da estrutura StackDirectory
 * @version 0.1
 * @date 2022-12-17
 * 
 * 
 */

#include "stackDirectory.h"

StackDirectory* createStackDirectory() {
  StackDirectory* stack = (StackDirectory*)malloc(sizeof(StackDirectory));
  stack->currentDirectory = NULL;
  stack->rootDirectory = NULL;
  stack->qtdDirectory = 0;

  return stack;
}

void push(StackDirectory* stack, NodeStackDirectory* node, char* name) {
  // Verificando a existência da stack e do nó
  if (stack == NULL) return;
  if (node == NULL) return;

  strcpy(node->name, name);

  node->next = NULL;
  // Caso a stack esteja vazia, apenas adiciona o node, fazendo current e root
  // directory apontar para o node. Caso contrário, adiciona o node e atualiza
  // as outras variáveis.
  if (stack->qtdDirectory == 0) {
    node->previous = NULL;
    stack->currentDirectory = node;
    stack->rootDirectory = node;
  } else {
    node->previous = stack->currentDirectory;
    stack->currentDirectory->next = node;
    stack->currentDirectory = node;
  }

  stack->qtdDirectory++; /* atualiza contador incrementando */ 
}

void pop(StackDirectory* stack) {
  // Verificando se há uma stack ou se a stack está vazia
  if (stack == NULL) return;
  if (stack->qtdDirectory == 0) return;

  NodeStackDirectory* node = stack->currentDirectory;

  // Faz o diretório atual apontar para o diretório anterior se este útlimo não
  // for nulo
  if (stack->currentDirectory->previous != NULL)
    stack->currentDirectory = stack->currentDirectory->previous;

  destroyListDirEntry(node->listDirEntry);
  free(node);

  stack->qtdDirectory--; /* atualiza contador decrementando */
}

void destroyStack(StackDirectory* stack) {
  if (stack == NULL) return;

  // Esvazia toda a stack antes de liberar o espaço alocado para a stack
  while (stack->qtdDirectory != 0) {
    pop(stack);
  }

  free(stack);
}
