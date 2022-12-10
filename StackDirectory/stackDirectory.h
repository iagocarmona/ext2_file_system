#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ListDirEntry/listDirEntry.h"
#include "../utils/utils.h"

typedef struct NodeStackDirectory {
  struct NodeStackDirectory* next;
  struct NodeStackDirectory* previous;
  struct ListDirEntry* listDirEntry;
  char name[20];
} NodeStackDirectory;

typedef struct StackDirectory {
  int qtdDirectory;
  struct NodeStackDirectory* currentDirectory;
  struct NodeStackDirectory* rootDirectory;
} StackDirectory;

struct StackDirectory* createStackDirectory();
void push(StackDirectory* stack, NodeStackDirectory* node, char* name);
void pop(StackDirectory* stack);
void destroyStack(StackDirectory* stack);
void readAllDirectoryAndPushIntoStack(FILE* file, struct ext2_group_desc* gdesc, struct ext2_super_block* super, struct StackDirectory* stack);
