#include "cat.h"

void catCommand(FILE* file, Inode inode, StackDirectory* stack, GroupDescriptor *group, Superblock* super, char* file_name){
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
			break;
        }

        // se chegou ao fim, finaliza
        if (dirEntry->next == NULL) break;

        dirEntry = dirEntry->next;
        entry = dirEntry->entry;
    }

	if(!found_file || !inode_no) {
		printf("Arquivo não encontrado.\n");
		return;
	}

	unsigned char block[BLOCK_SIZE];

	int read_block_pos = 0;

	int simple_ind_pos = 0;
	int double_ind_pos = 0;
	int triple_ind_pos = 0;

	int amount_ind_pointers = BLOCK_SIZE / sizeof(unsigned int);

	unsigned int* singleInd = (unsigned int*)malloc(amount_ind_pointers * sizeof(unsigned int));
	unsigned int* doubleInd = (unsigned int*)malloc(amount_ind_pointers * sizeof(unsigned int));
	unsigned int* tripleInd = (unsigned int*)malloc(amount_ind_pointers * sizeof(unsigned int));

	if(inode.i_mode & 0x4000){
		printf(RED("ERROR:") " comando" CYAN(" cat ") "funciona apenas com arquivos.\n");
	}else {
		while(read_block_pos < 12){
			int offset = BLOCK_OFFSET(inode.i_block[read_block_pos]);

			if(!inode.i_block[read_block_pos]) break;

			fseek(file, offset, SEEK_SET);
			fread(block, BLOCK_SIZE, 1, file);

			printf("%s", block);
			read_block_pos++;
		}

		if(read_block_pos == 12){
			int offset = BLOCK_OFFSET(inode.i_block[read_block_pos]);

			if(!inode.i_block[read_block_pos]) return;

			fseek(file, offset, SEEK_SET);
			fread(singleInd, BLOCK_SIZE, 1, file);

			while(simple_ind_pos < amount_ind_pointers){
				int offset = BLOCK_OFFSET(singleInd[simple_ind_pos]);

				if(!singleInd[simple_ind_pos]) break;

				fseek(file, offset, SEEK_SET);
				fread(block, BLOCK_SIZE, 1, file);

				printf("%s", block);
				simple_ind_pos++;
			}
			read_block_pos++;
			simple_ind_pos = 0;
			memset(singleInd, 0, amount_ind_pointers);
		}


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

	free(singleInd);
	free(doubleInd);
	free(tripleInd);
}