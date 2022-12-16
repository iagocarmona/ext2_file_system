#include "listDirEntry.h"

ListDirEntry* createListDirEntry() {
  ListDirEntry* list = (ListDirEntry*)malloc(sizeof(ListDirEntry));
  list->head = NULL;
  list->tail = NULL;
  list->qtdDirEntries = 0;

  return list;
}

static struct ext2_dir_entry_2* insertInTheLastPosition(ListDirEntry* list,
                                         NodeDirEntry* entry) {
  struct NodeDirEntry* aux = list->head;

  // Procura pelo fim da lista de DirEntry
  while (aux->next != NULL) {
    aux = aux->next;
  }

  // Insere novo nó
  entry->previous = aux;
  aux->next = entry;

  return entry->entry;
}

void removeLastDirEntry(ListDirEntry* list) {
  if (list == NULL) return;

  NodeDirEntry* aux = list->tail;

  // Atualiza a fila
  list->tail = aux->previous;
  if (aux->previous != NULL) aux->previous->next = NULL;

  free(aux->entry);
  free(aux);

  list->qtdDirEntries--;

  if (list->qtdDirEntries == 0) {
    list->tail = NULL;
    list->head = NULL;
  };
}

static struct ext2_dir_entry_2* insertInPosition(ListDirEntry* list, NodeDirEntry* entry,
                                  int position) {
  struct NodeDirEntry* aux = list->head;

  int idx = 0;

  // Percorre a lista enquanto não chegar na posição ou enquanto a próxima
  // DirEntry não dor nula
  while (idx != position && aux->next != NULL) {
    aux = aux->next;
    idx++;
  }

  // Atualiza as informações da lista
  free(aux->entry);
  aux->entry = entry->entry;
  free(entry);

  return aux->entry;
}

struct ext2_dir_entry_2* insertDirEntry(ListDirEntry* list, NodeDirEntry* entry, int* position) {
  if (list == NULL) return NULL;
  if (entry == NULL) return NULL;

  struct ext2_dir_entry_2* returnedEntry = NULL;

  // Verifica se a DirEntry será inserida no meio ou no fim da lista
  int insertInTheMiddleOfList = (position != NULL) && (*position < list->qtdDirEntries);

  if (list->qtdDirEntries == 0) {
    list->head = entry;
    list->tail = entry;
    list->qtdDirEntries++;
    returnedEntry = entry->entry;
  } else if (insertInTheMiddleOfList) {
    returnedEntry = insertInPosition(list, entry, *position);
  } else {
    returnedEntry = insertInTheLastPosition(list, entry);
    list->tail = entry;
    list->qtdDirEntries++;
  }

  return returnedEntry;
}

void destroyListDirEntry(ListDirEntry* list) {
  if (list == NULL) return;

  struct NodeDirEntry* entry = list->head;

  if (entry != NULL) {
    // Percorre a lista de DirEntry e libera o espaço das entradas
    for (int i = 0; i < list->qtdDirEntries; i++) {
      struct NodeDirEntry* nextEntry = entry->next;

      free(entry->entry);
      free(entry);
      entry = nextEntry;
    }

    free(entry);
  }

  free(list);
}
