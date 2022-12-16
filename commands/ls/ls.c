/**
 * @file ls.c
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de implementação da função que realiza o comando ls
 * @version 0.1
 * @date 2022-12-16
 * 
 * 
 */

#include "ls.h"

void lsCommand(FILE* file, struct ext2_inode inode, struct ext2_group_desc *group){
    
    void *block;

	if (S_ISDIR(inode.i_mode)) { /* verifica se inode é de tipo diretório */
		struct ext2_dir_entry_2 *entry; /* incializa estrututa de lista de entradas */
		unsigned int size = 0; /* incializa variável de comprimento */

		if ((block = malloc(BLOCK_SIZE)) == NULL) { /* aloca memória para o boco de dados  */
			fprintf(stderr, "Memory error\n");
			fclose(file);
			exit(1);
		}

		fseek(file, BLOCK_OFFSET(inode.i_block[0]), SEEK_SET); /* posiciona ponteiro da imagem */
		fread(block, BLOCK_SIZE, 1, file);                /* lê bloco do disco */

		entry = (struct ext2_dir_entry_2 *) block;  /* primeira entrada no diretório */
		
		while((size < inode.i_size) && entry->inode) { /* enquanto não exceder */
			char file_name[EXT2_NAME_LEN+1];
			memcpy(file_name, entry->name, entry->name_len); /* copia nome do arquivo para a variável de comparação */
			file_name[entry->name_len] = 0;     /* caractere nulo para o nome de arquivo */
			
            printf("%s\n", file_name); /* nome do diretório */
            printf("inode: %u\n", entry->inode); /* inode */
            printf("record lenght: %u\n", entry->rec_len); /* tamanho */
            printf("name lenght: %u\n", entry->name_len); /* nome */
            printf("file type: %u\n", entry->file_type); /* tipo */

			entry = (void*) entry + entry->rec_len; /* atualiza */
			size += entry->rec_len; /* incrementa comprimento */
		}
		printf("\n");
		free(block); /* libera bloco alocado */
	}
}