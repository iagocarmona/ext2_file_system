#include "cd.h"

static inline void popToRootDir(StackDirectory* stackDirectory) {
  // Se houver apenas um diretório, significa que ele já está no diretório raíz.
  if (stackDirectory->qtdDirectory == 1) return;

  // Desempilha os diretórios até chegar no diretório raíz.
  while (strcmp(stackDirectory->currentDirectory->name, "/") != 0) {
    pop(stackDirectory);
  }
}

int cdCommand(FILE* file, GroupDescriptor *group, StackDirectory* stack, Superblock* super, char* path){
    struct NodeDirEntry* dirEntry = stack->currentDirectory->listDirEntry->head;
    DirEntry* entry = dirEntry->entry;

    // Entrada vazia é inválida
    if (strlen(path) == 0) return 0;

    // Obtêm o caminho absoluto do diretório atual
    char* currentPath = pwdCommand(stack);

    // Se o caminho a ser atingido é o mesmo do caminho atual,
    // a função é apenas encerrada retornando sucesso
    if (strcmp(path, currentPath) == 0) {
        free(currentPath);
        return 1;
    }

    // Caso o destino for o diretório raíz, atribui o diretório raiz à stackDirectory
    if (strlen(path) == 1 && path[0] == '/') {
        popToRootDir(stack);
        return 1;
    }

    int found_file = 0;

    while(1){
        char file_name[EXT2_NAME_LEN+1];
		memcpy(file_name, entry->name, entry->name_len);
		file_name[entry->name_len] = 0; 

        if(strcmp(path, ".") == 0){
            found_file = 1;
            continue;
        }

        if(strcmp(path, "..") == 0) {
            if (stack->qtdDirectory == 1) {
                printf("Não existe diretório anterior!\n");
                break;
            }
            found_file = 1;
            pop(stack);
            break;
        }

        if(strcmp(file_name, path) == 0){
            uint32_t inode_no = entry->inode;
            Inode inode;
            read_inode(file, inode_no, group, &inode, super);
            found_file = 1;

            char file_type = 0;

            if(inode.i_mode & 0x4000) file_type = 'd';

            // Verifica se o diretório é válido
            if (!inode_no) {
                printf("Caminho inválido: %s\n", path);
                return -1;
            }

            // Verifica se a entrada é um diretório
            if(file_type != 'd'){
                printf("Caminho não é um diretório: %s\n", path);
                return -1;
            }

            read_all_dirs_and_push_into_stack(file, &inode, group, stack, path);
            break;
        }

        // se chegou ao fim, finaliza
        if (dirEntry->next == NULL) break;

        dirEntry = dirEntry->next;
        entry = dirEntry->entry;
    }

    if(!found_file){
        printf("Diretório inválido.\n");
        return -1;
    } 
}   