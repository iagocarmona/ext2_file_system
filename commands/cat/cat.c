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
        }

        // se chegou ao fim, finaliza
        if (dirEntry->next == NULL) break;

        dirEntry = dirEntry->next;
        entry = dirEntry->entry;
    }

	if(!found_file || !inode_no) return;

	read_inode(file, inode_no, group, &inode, super);

	unsigned char block[BLOCK_SIZE];

	if(inode.i_mode & 0x4000){
		printf(RED("ERROR:") " comando" CYAN(" cat ") "funciona apenas com arquivos.\n");
	}else {
		fseek(file, BLOCK_OFFSET(inode.i_block[0]), SEEK_SET);
		fread(block, BLOCK_SIZE, 1, file);  

		printf("%s", block);
	}
}