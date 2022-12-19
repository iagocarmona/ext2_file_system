/**
 * @file cat.c
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de implementação da função que executa o comando cat
 *
 * Data de criação: 28/11/2022 
 * Datas de modificações: 09/12/2022, 15/12/2022, 17/12/2022
 * 
 */

#include "cat.h"

void catCommand(FILE* file, Inode inode, StackDirectory* stack, GroupDescriptor *group, Superblock* super, char* file_name){
	char found_file = 0;
	uint32_t inode_no;

	struct NodeDirEntry* dirEntry = stack->currentDirectory->listDirEntry->head;
    DirEntry* entry = dirEntry->entry;

	// verificando se o arquivo existe no diretório atual
	while(1){
        char fileName[EXT2_NAME_LEN+1];
		memcpy(fileName, entry->name, entry->name_len);
		fileName[entry->name_len] = 0; 

		// se existir, lê o inode dele
        if(strcmp(fileName, file_name) == 0){
            inode_no = entry->inode;
            read_inode(file, inode_no, group, &inode, super);
            found_file = 1;
			break;
        }

        // se chegou ao fim, finaliza
        if (dirEntry->next == NULL) break;

		// Apontando para o próximo NodeDirEntry
        dirEntry = dirEntry->next;
        entry = dirEntry->entry;
    }

	// Se não encontrou o inode e nem o arquivo, então exibe a informação da linha 46.
	if(!found_file || !inode_no) {
		printf("Arquivo não encontrado.\n");
		return;
	}

	unsigned char block[BLOCK_SIZE];

	// posição atual do ponteiro de bloco
	int read_block_pos = 0;

	// posição atual dos tipos de indireções.
	int simple_ind_pos = 0;
	int double_ind_pos = 0;
	int triple_ind_pos = 0;

	// variável que armazena a quantidade de ponteiros de indireção dado um BLOCK_SIZE
	int amount_ind_pointers = BLOCK_SIZE / sizeof(unsigned int);

	// Inicializando ponteiros para alocar os endereços dos blocos em cada tipo de indireção
	unsigned int* singleInd = (unsigned int*)malloc(amount_ind_pointers * sizeof(unsigned int));
	unsigned int* doubleInd = (unsigned int*)malloc(amount_ind_pointers * sizeof(unsigned int));
	unsigned int* tripleInd = (unsigned int*)malloc(amount_ind_pointers * sizeof(unsigned int));

	if(inode.i_mode & 0x4000){
		printf(RED("ERROR:") " comando" CYAN(" cat ") "funciona apenas com arquivos.\n");
	}else {
		// lendo os 12 primeiros blocos, pois estes são ponteiros diretos.
		while(read_block_pos < 12){
			int offset = BLOCK_OFFSET(inode.i_block[read_block_pos]);

			// verifica se está vazio e então finaliza
			if(!inode.i_block[read_block_pos]) break;

			fseek(file, offset, SEEK_SET);
			fread(block, BLOCK_SIZE, 1, file);

			// exibe as informaçẽos de cada bloco lido
			printf("%s", block);
			read_block_pos++;
		}

		// Aqui está tratando o primeiro nível de indireção.
		if(read_block_pos == 12){
			int offset = BLOCK_OFFSET(inode.i_block[read_block_pos]);

			// verifica se está vazio e então finaliza
			if(!inode.i_block[read_block_pos]) return;

			fseek(file, offset, SEEK_SET);
			fread(singleInd, BLOCK_SIZE, 1, file);

			// laço que percorre por todos os ponteiros
			while(simple_ind_pos < amount_ind_pointers){
				//pegando o offset do bloco em cada endereço de indireção
				int offset = BLOCK_OFFSET(singleInd[simple_ind_pos]);

				// verifica se está vazio e então finaliza
				if(!singleInd[simple_ind_pos]) break;

				fseek(file, offset, SEEK_SET);
				fread(block, BLOCK_SIZE, 1, file);

				// exibe as informações de cada bloco
				printf("%s", block);
				simple_ind_pos++;
			}
			read_block_pos++;
			simple_ind_pos = 0;

			// zerando o  valolr de indireção para não dar conflito
			memset(singleInd, 0, amount_ind_pointers);
		}

		// Aqui está tratando o segundo nível de indireção.
		// Seguindo a mesma lógica do nível anterior, porém com um nível a mais,
		if(read_block_pos == 13){
			int offset = BLOCK_OFFSET(inode.i_block[read_block_pos]);

			if(!inode.i_block[read_block_pos]) return;

			fseek(file, offset, SEEK_SET);
			fread(singleInd, BLOCK_SIZE, 1, file);

			while(simple_ind_pos < amount_ind_pointers){
				int offset = BLOCK_OFFSET(singleInd[simple_ind_pos]);

				if(!singleInd[simple_ind_pos]) break;

				fseek(file, offset, SEEK_SET);
				fread(doubleInd, BLOCK_SIZE, 1, file);

				while(double_ind_pos < amount_ind_pointers){
					offset = BLOCK_OFFSET(doubleInd[double_ind_pos]);

					if(!doubleInd[double_ind_pos]) break;

					fseek(file, offset, SEEK_SET);
					fread(block, BLOCK_SIZE, 1, file);

					printf("%s", block);
					double_ind_pos++;
				}
				memset(doubleInd, 0, amount_ind_pointers);
				double_ind_pos = 0;
				simple_ind_pos++;
			}
			read_block_pos++;
			simple_ind_pos = 0;
			double_ind_pos = 0;
			memset(singleInd, 0, amount_ind_pointers);
		}

		// Aqui está tratando o terceiro nível de indireção.
		// Seguindo a mesma lógica do nível anterior, porém com um nível a mais,
		if(read_block_pos == 14){
			int offset = BLOCK_OFFSET(inode.i_block[read_block_pos]);

			if(!inode.i_block[read_block_pos]) return;

			fseek(file, offset, SEEK_SET);
			fread(singleInd, BLOCK_SIZE, 1, file);

			while(simple_ind_pos < amount_ind_pointers){
				int offset = BLOCK_OFFSET(singleInd[simple_ind_pos]);

				if(!singleInd[simple_ind_pos]) break;

				fseek(file, offset, SEEK_SET);
				fread(doubleInd, BLOCK_SIZE, 1, file);

				while(double_ind_pos < amount_ind_pointers){
					offset = BLOCK_OFFSET(doubleInd[double_ind_pos]);

					if(!doubleInd[double_ind_pos]) break;

					fseek(file, offset, SEEK_SET);
					fread(tripleInd, BLOCK_SIZE, 1, file);

					while(triple_ind_pos < amount_ind_pointers){
						offset = BLOCK_OFFSET(tripleInd[triple_ind_pos]);

						if(!tripleInd[triple_ind_pos]) break;

						fseek(file, offset, SEEK_SET);
						fread(block, BLOCK_SIZE, 1, file);

						printf("%s", block);
						triple_ind_pos++;
					}
					triple_ind_pos = 0;
					memset(tripleInd, 0, amount_ind_pointers);
					double_ind_pos++;
				}
				memset(doubleInd, 0, amount_ind_pointers);
				double_ind_pos = 0;
				simple_ind_pos++;
			}
			
		}
	}

	// desalocando as memória dinâmicas
	free(singleInd);
	free(doubleInd);
	free(tripleInd);
}