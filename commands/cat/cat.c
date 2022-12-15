#include "cat.h"

void catCommand(FILE* file, struct ext2_inode inode, struct ext2_group_desc *group, struct ext2_super_block* super, char* file_name){
	uint32_t inode_no = read_dir(file, &inode, group, file_name);
	read_inode(file, inode_no, group, &inode, super);

	if(!inode_no) return;

	unsigned char block[BLOCK_SIZE];

	if(inode.i_mode & 0x4000){
		printf(RED("ERROR:") " comando" CYAN(" cat ") "funciona apenas com arquivos.\n");
	}else {
		fseek(file, BLOCK_OFFSET(inode.i_block[0]), SEEK_SET);
		fread(block, BLOCK_SIZE, 1, file);  

		printf("%s", block);
	}
}