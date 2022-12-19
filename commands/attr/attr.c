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

    // laço que percorre por todos os DirEntry e verifica o nome,
    // se existe, então já lê o inode dele.
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

        // Apontando para o próximo nodeDirEntry.
        dirEntry = dirEntry->next;
        entry = dirEntry->entry;
    }
    
    // Se não encontrar o inode e a variável found_file nunca foi setada para 1,
    // então arquivo/diretório nao existe no diretório atual.
    if(!inode_no || !found_file){
        printf(RED("ERROR: ")"Arquivo/Diretório não encontrado.\n");
        return;
    }
    
    int mode = inode.i_mode;    

    // inicializando variáveis que representarão as permissões do arquivo
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

    // realizando calculo de bytes e KiB
    if(inode.i_size < 1024){
        size = inode.i_size;
        size_text = "Bytes";
    }else {
        size = inode.i_size / 1024;
        size_text = "KiB";
    }

    char* mtime = convert_num_to_unix_time(inode.i_mtime);

    printf("permissões\tuid\tgid\ttamanho\t\tmodificado em\n");
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