/**
 * @file attr.c
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de implementação das funções usadas para o comando attr
 * 
 * Data de criação: 28/11/2022,
 * Datas de modificações: 09/12/2022, 15/12/2022, 17/12/2022
 * 
 */


#include "attr.h"

void attrCommand(FILE* file, Inode inode, StackDirectory* stack, GroupDescriptor *group, Superblock* super, char* file_name){
    char found_file = 0;
	uint32_t inode_no;

	struct NodeDirEntry* dirEntry = stack->currentDirectory->listDirEntry->head;
    DirEntry* entry = dirEntry->entry;

    while(1){
        char fileName[EXT2_NAME_LEN+1];
		memcpy(fileName, entry->name, entry->name_len);
		fileName[entry->name_len] = 0; 

        if(strcmp(fileName, file_name) == 0){
            inode_no = entry->inode;
            read_inode(file, inode_no, group, &inode, super);
            found_file = 1;
        }

        // se chegou ao fim, finaliza
        if (dirEntry->next == NULL) break;

        dirEntry = dirEntry->next;
        entry = dirEntry->entry;
    }
    
    if(!inode_no || !found_file) {
        printf("Arquivo não encontrado\n");
        return;
    }
    
    int mode = inode.i_mode;  /* formato e atributos do inode */   
    char file_type,
         user_read,
         user_write,
         user_execute,
         group_read,
         group_write,
         group_execute,
         others_read,
         others_write,
         others_execute;

    if(mode & 0x4000) file_type = 'd';
    if(mode & 0x8000) file_type = 'f';

    // ================ user fields ============== 

    user_read = mode & 0x0100 ? 'r' : '-';
    user_write = mode & 0x0080 ? 'w' : '-';
    user_execute = mode & 0x0040 ? 'x' : '-';

    // ================ groud fields ============== 

    group_read = mode & 0x0100 ? 'r' : '-';
    group_write = mode & 0x0080 ? 'w' : '-';
    group_execute = mode & 0x0040 ? 'x' : '-';

    // ================ others fields ============== 

    others_read = mode & 0x0100 ? 'r' : '-';
    others_write = mode & 0x0080 ? 'w' : '-';
    others_execute = mode & 0x0040 ? 'x' : '-';

    float size;
    char* size_text;

    if(inode.i_size < 1024){
        size = inode.i_size;
        size_text = "Bytes";
    }else {
        size = inode.i_size / 1024;
        size_text = "KiB";
    }

    char* mtime = convertNumToUnixTime(inode.i_mtime); /* coverte hora da montagem do arquio em UNIX */

    printf("permissões\tuid\tgid\ttamanho\t\tmodificado em\n"); /* exibe atributos do aqruivo */
    printf("%c%c%c%c%c%c%c%c%c%c\t%u\t%u\t%.2f %s\t%s\n", 
            file_type,
            user_read,
            user_write,
            user_execute,
            group_read,
            group_write,
            group_execute,
            others_read,
            others_write,
            others_execute,
            inode.i_uid,
            inode.i_gid,
            size,
            size_text,
            mtime);
}