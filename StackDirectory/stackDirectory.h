#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ListDirEntry/listDirEntry.h"
#include "../utils/utils.h"

/**
 * @brief node que compõem a pilha de diretórios
 * 
 */
typedef struct NodeStackDirectory {
  struct NodeStackDirectory* next;
  struct NodeStackDirectory* previous;
  struct ListDirEntry* listDirEntry;
  char name[20];
} NodeStackDirectory;

/**
 * @brief struct da pilha de diretórios
 * 
 */
typedef struct StackDirectory {
  int qtdDirectory;
  struct NodeStackDirectory* currentDirectory;
  struct NodeStackDirectory* rootDirectory;
} StackDirectory;

/**
 * @brief cria uma struct StackDirectory 
 * 
 * @return struct StackDirectory* 
 */
struct StackDirectory* createStackDirectory();



/**
 * @brief adiciona node no topo da pilha
 * 
 * @param stack StackDirectory onde o node será armazenado
 * @param node que será adicionado
 * @param name nome do node
 */
void push(StackDirectory* stack, NodeStackDirectory* node, char* name);



/**
 * @brief remove node do topo da pilha
 * 
 * @param stack StackDirectory do qual o node do topo será retirado
 */
void pop(StackDirectory* stack);



/**
 * @brief destrói StackDiretory
 * 
 * @param stack tackDirectory que será destruído
 */
void destroyStack(StackDirectory* stack);



/**
 * @brief 
 * 
 * @param file 
 * @param gdesc 
 * @param super 
 * @param stack 
 */
void readAllDirectoryAndPushIntoStack(FILE* file, struct ext2_group_desc* gdesc, struct ext2_super_block* super, struct StackDirectory* stack);
