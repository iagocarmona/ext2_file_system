#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

// ext2
#include "ext2/ext2.h"

// utils
#include "utils/utils.h"

#define IMAGE "./myext2image.img"              /* the floppy disk device */
#define BLOCK_SIZE 1024


int main(){
	FILE *file = fopen(IMAGE, "rb+");
	struct ext2_super_block super;

	fseek(file, 1024, SEEK_CUR);
  	fread(&super, sizeof(ext2_super_block), 1, file);

	print_superblock(super);

	exit(0);
}