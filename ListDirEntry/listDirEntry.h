/**
 * @file listDirEntry.h
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de declaração das funções de manipulação das estruturas ListDirEntry
 * e NodeDirEntry
 * 
 * Data de criação: 07/12/2022
 * Datas de modificações: 16/12/2022
 * 
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../EXT2/ext2.h"


/**
 * @brief armazena nós de ListDirEntry
 * 
 */
typedef struct NodeDirEntry {
  struct NodeDirEntry* next;
  struct NodeDirEntry* previous;
  struct ext2_dir_entry_2* entry;
} NodeDirEntry;


/**
 * @brief armazena estruturas DirEntry que estçao dentro de seu respectivo diretório
 * 
 */
typedef struct ListDirEntry {
  int qtdDirEntries;
  struct NodeDirEntry* head;
  struct NodeDirEntry* tail;
} ListDirEntry;


/**
 * @brief cria estrutura ListDirEntry
 * 
 * @return ListDirEntry* 
 */
ListDirEntry* createListDirEntry();


/**
 * @brief insere entrada de diretório na lista de diretórios
 * 
 * @param list onde será inderido
 * @param entry oque será inserido
 * @param position lugar da lista que será inserido
 * @return struct ext2_dir_entry_2* 
 */
struct ext2_dir_entry_2* insertDirEntry(ListDirEntry* list, NodeDirEntry* entry, int* position);


/**
 * @brief destrói lista de diretórios
 * 
 * @param list 
 */
void destroyListDirEntry(ListDirEntry* list);



/**
 * @brief remove última entrada de diretório da lista
 * 
 * @param list 
 */
void removeLastDirEntry(ListDirEntry* list);