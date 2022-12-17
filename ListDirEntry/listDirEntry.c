/**
 * @file listDirEntry.c
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de implementação das funções de manipulação das estruturas
 * @version 0.1
 * @date 2022-12-17
 * 
 * 
 */
#include "listDirEntry.h"

ListDirEntry* createListDirEntry() {
  ListDirEntry* list = (ListDirEntry*)malloc(sizeof(ListDirEntry)); /* alocação */

  /****incialização das variáveis da struct*****/
  list->head = NULL; 
  list->tail = NULL; 
  list->qtdDirEntries = 0;
  list->amountOfCluster = 0;


  return list; /* retorna a struct */
}

static struct ext2_dir_entry_2* insertInTheLastPosition(ListDirEntry* list,
                                         NodeDirEntry* entry) {

  struct NodeDirEntry* aux = list->head; /* pega o que está no "topo" da lista */

  // Procura pelo fim da lista de DirEntry
  while (aux->next != NULL) {
    aux = aux->next;
  }

  // Insere novo nó
  entry->previous = aux;
  aux->next = entry;

  return entry->entry; /* retorna diretório de entrada */
}

void removeLastDirEntry(ListDirEntry* list) {
  if (list == NULL) return;

  NodeDirEntry* aux = list->tail;

  // Caso já estiver no último, apenas decrementa a quantidade de clusters.
  if (aux->previous != NULL) {
    // Caso não seja a última posição, mas seja o último elemento da lista,
    // decrementa a quantidade de clusters.
    if (aux->cluster != aux->previous->cluster) {
      list->amountOfCluster--;
    }
  } else {
    list->amountOfCluster--;
  }

  // Atualiza a fila
  list->tail = aux->previous;
  if (aux->previous != NULL) aux->previous->next = NULL;

  free(aux->entry);
  free(aux);

  list->qtdDirEntries--; /* atualiza contador*/

  if (list->qtdDirEntries == 0) { /* caso não tenho mais diretórios */
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
  aux->cluster = entry->cluster;
  aux->entry = entry->entry;
  free(entry);

  return aux->entry;
}

struct ext2_dir_entry_2* insertDirEntry(ListDirEntry* list, NodeDirEntry* entry,
                         int* position) {
  if (list == NULL) return NULL;
  if (entry == NULL) return NULL;

  struct ext2_dir_entry_2* returnedEntry = NULL;

  // Verifica se a DirEntry será inserida no meio ou no fim da lista
  int insertInTheMiddleOfList =
      (position != NULL) && (*position < list->qtdDirEntries);

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
