#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/fs.h>

#define BASE_OFFSET 1024                   /* locates beginning of the super block (first group) */
#define IMAGE "myext2image.img"              /* the floppy disk device */

static unsigned int block_size = 0;        /* block size (to be calculated) */

int main(){
    int fd;
    struct ext2_super_block super;

    fd = open("myext2image.img", O_RDONLY);

    lseek(fd, SUPER_BLOCK_OFFSET, SEEK_SET);
    read(fd, &super, sizeof(super));

    if(super.s_magic != EXT2_SUPER_MAGIC)
        exit(1);

    block_size = BLOCK_SIZE << super.s_log_block_size;

    printf("Reading super-block from device " IMAGE ":\n"
	       "Inodes count.............: %u\n"
	       "Blocks count.............: %u\n"
	       "Reserved blocks count....: %u\n"
	       "Free blocks count........: %u\n"
	       "Free inodes count........: %u\n"
	       "First data block.........: %u\n"
	       "Block size...............: %u\n"
	       "Blocks per group.........: %u\n"
	       "Inodes per group.........: %u\n"
	       "Creator OS...............: %u\n"
	       "First non-reserved inode.: %u\n"
	       "Size of inode structure..: %hu\n"
	       ,
	       super.s_inodes_count,  
	       super.s_blocks_count,
	       super.s_r_blocks_count,     /* reserved blocks count */
	       super.s_free_blocks_count,
	       super.s_free_inodes_count,
	       super.s_first_data_block,
	       block_size,
	       super.s_blocks_per_group,
	       super.s_inodes_per_group,
	       super.s_creator_os,
	       super.s_first_ino,          /* first non-reserved inode */
	       super.s_inode_size);
	
	exit(0);
}