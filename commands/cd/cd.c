/**
 * @file cd.c
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de implementação da função que realiza o comando cd
 * @version 0.1
 * @date 2022-12-16
 * 
 */


#include "cd.h"

void cdCommand(FILE* file, struct ext2_inode *inode, struct ext2_group_desc *group, char* nomeArquivo){
    void *block;

	if (S_ISDIR(inode->i_mode)) { /* verifica se é diretório */
		struct ext2_dir_entry_2 *entry;
		unsigned int size = 0;

		if ((block = malloc(BLOCK_SIZE)) == NULL) { /* aloca memória para o boco de dados  */
			fprintf(stderr, "Memory error\n");
			fclose(file);
			exit(1);
		}

		fseek(file, BLOCK_OFFSET(inode->i_block[0]), SEEK_SET); /* posiciona ponteiro da imagem */
		fread(block, BLOCK_SIZE, 1, file);                /* lê bloco do disco */

		entry = (struct ext2_dir_entry_2 *) block;  /* primeira entrada no diretório */
      
		int found_file = 0;
		
		while((size < inode->i_size) && entry->inode) {
			char file_name[EXT2_NAME_LEN+1];
			memcpy(file_name, entry->name, entry->name_len); /* copia nome do arquivo para a variável de comparação */
			file_name[entry->name_len] = 0;     /* caractere nulo para o nome de arquivo */
			if(strcmp(nomeArquivo, file_name) == 0){ /* verifica se arquivo foi encontrado  */
				
                if(entry->file_type == 2){ /* verifica se a entrda é do tipo diretório */
                    printf("%s\n", entry->name);
                    printf("inode: %u\n", entry->inode);
                    printf("record lenght: %u\n", entry->rec_len);
                    printf("name lenght: %u\n", entry->name_len);
                    printf("file type: %u\n", entry->file_type);
                } else{
                    printf("Não é um diretório\n");
                }
				
			}
			// printf("%10u %s\n", entry->inode, file_name);
			entry = (void*) entry + entry->rec_len;
			size += entry->rec_len;
		}

		if(!found_file) printf(RED("Arquivo ou diretório inexistente")); /* informa caso o arquivo não foi encontrado */
		printf("\n");
		free(block); /* libera bloco alocado */
	}
} 