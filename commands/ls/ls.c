/**
 * @file ls.c
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de implemetação da função que realiza o comando ls
 * 
 * Data de criação: 28/11/2022
 * 
 */

#include "ls.h"

void lsCommand(ListDirEntry *listDirEntry){
    struct NodeDirEntry* dirEntry = listDirEntry->head;
    DirEntry* entry = dirEntry->entry;

    // se não tiver nada, apenas retorna
    if (dirEntry == NULL) return;

    while(1){
        printf("\n");
        char file_name[EXT2_NAME_LEN+1];
		memcpy(file_name, entry->name, entry->name_len);
		file_name[entry->name_len] = 0;     

        // exibe informações 
        printf("%s\n", file_name);
        printf("inode: %d\n", entry->inode);
        printf("record lenght: %d\n", entry->rec_len);
        printf("name lenght: %d\n", entry->name_len);
        printf("file type: %d\n", entry->file_type);

        // se chegou ao fim, finaliza
        if (dirEntry->next == NULL) break;

        dirEntry = dirEntry->next;
        entry = dirEntry->entry;
    }
}