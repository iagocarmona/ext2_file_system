#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../EXT2/ext2.h"


/**
 * @brief struct dos diretórios de entrada
 * 
 */
typedef struct NodeDirEntry {
  struct NodeDirEntry* next;
  struct NodeDirEntry* previous;
  struct ext2_dir_entry_2* entry;
  uint32_t cluster;
} NodeDirEntry;

/**
 * @brief struct da lista de diretórios de entrada
 * 
 */
typedef struct ListDirEntry {
  int qtdDirEntries;
  int amountOfCluster;
  struct NodeDirEntry* head;
  struct NodeDirEntry* tail;
} ListDirEntry;

/**
 * @brief cria um ListDirEntry
 * 
 * @return ListDirEntry* 
 */
ListDirEntry* createListDirEntry();



/**
 * @brief inserte diretório na lista
 * 
 * @param list onde será inserida
 * @param entry diretório de entrada que será inserido
 * @param position 
 * @return struct ext2_dir_entry_2* 
 */
struct ext2_dir_entry_2* insertDirEntry(ListDirEntry* list, NodeDirEntry* entry, int* position);



/**
 * @brief  destrói a struct ListDirEntry referenciada
 * 
 * @param list struct ListDirEntry referenciada
 */
void destroyListDirEntry(ListDirEntry* list);



/**
 * @brief remove o último diretório da lista
 * 
 * @param list 
 */
void removeLastDirEntry(ListDirEntry* list);