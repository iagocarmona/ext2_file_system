/**
 * @file utils.c
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de declaração das funções de manipulação das estruturas NodeStackDirectory
 * e StackDirectory
 * 
 * Data de criação: 07/12/2022
 * Datas de modificações: 15/12/2022, 16/12/2022
 * 
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ListDirEntry/listDirEntry.h"

/**
 * @brief estrutura que armazena os diretórios carregados
 * 
 */
typedef struct NodeStackDirectory {
  struct NodeStackDirectory* next;
  struct NodeStackDirectory* previous;
  struct ListDirEntry* listDirEntry;
  char name[255];
} NodeStackDirectory;


/**
 * @brief estrutura que armazena informações dos diretórios 
 * que um diretório referencia
 * 
 */
typedef struct StackDirectory {
  int qtdDirectory;
  struct NodeStackDirectory* currentDirectory;
  struct NodeStackDirectory* rootDirectory;
} StackDirectory;


/**
 * @brief cria estrutura StackDirectory
 * 
 * @return struct StackDirectory* 
 */
struct StackDirectory* createStackDirectory();


/**
 * @brief adiciono nó no topo da pilha
 * 
 * @param stack 
 * @param node oque será adicionado
 * @param name nome do nó
 */
void push(StackDirectory* stack, NodeStackDirectory* node, char* name);


/**
 * @brief remove nó do topo da pilha
 * 
 * @param stack pilha da qual nó será removido
 */
void pop(StackDirectory* stack);


/**
 * @brief destrói pilha de diretórios
 * 
 * @param stack pilha que será destruída
 */
void destroyStack(StackDirectory* stack);