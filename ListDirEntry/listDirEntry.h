#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../EXT2/ext2.h"

typedef struct NodeDirEntry {
  struct NodeDirEntry* next;
  struct NodeDirEntry* previous;
  struct ext2_dir_entry_2* entry;
  uint32_t cluster;
} NodeDirEntry;

typedef struct ListDirEntry {
  int qtdDirEntries;
  int amountOfCluster;
  struct NodeDirEntry* head;
  struct NodeDirEntry* tail;
} ListDirEntry;

ListDirEntry* createListDirEntry();
struct ext2_dir_entry_2* insertDirEntry(ListDirEntry* list, NodeDirEntry* entry, int* position);
void destroyListDirEntry(ListDirEntry* list);
void removeLastDirEntry(ListDirEntry* list);