/**
 * @file info.c
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de implementação da função usada para o comando info
 * 
 * Data de criação: 28/11/2022
 * Datas de modificações: 07/12/2022
 * 
 */

#include "info.h"

void infoCommand(struct ext2_super_block* super){
	// calculos para chegar nas informações corretas utilizando o super bloco.
    uint32_t image_size = super->s_blocks_count * super->s_log_block_size;
    uint32_t free_space = (super->s_free_blocks_count * super->s_log_block_size) / 1024;
    uint32_t groups_count = 1 + (super->s_blocks_count-1) / super->s_blocks_per_group;
    uint32_t inodetable_size = (super->s_inodes_per_group * super->s_inode_size) / 1024;

    printf("\n");
	printf("Volume name.....: %s\n"
		   "Image size......: %" PRIu32 " bytes\n"
		   "Free space......: %" PRIu32 " KiB\n"
		   "Free inodes.....: %" PRIu32 "\n"
		   "Free blocks.....: %" PRIu32 "\n"
		   "Block size......: %" PRIu32 " bytes\n"
		   "Inode size......: %" PRIu32 " bytes\n"
		   "Groups count....: %" PRIu32 "\n"
		   "Groups size.....: %" PRIu32 " blocks\n"
		   "Groups inodes...: %" PRIu32 " inodes\n"
		   "Inodetable size.: %" PRIu32 " blocks\n"
		   ,
		   super->s_volume_name,
		   image_size,
		   free_space,
		   super->s_free_inodes_count,
		   super->s_free_blocks_count,
		   super->s_log_block_size,
		   super->s_inode_size,
           groups_count,
           super->s_blocks_per_group,
           super->s_inodes_per_group,
           inodetable_size);
	printf("\n");
}