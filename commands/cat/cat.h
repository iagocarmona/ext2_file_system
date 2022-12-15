#pragma once

#include "../../EXT2/ext2.h"
#include "../../utils/utils.h"

/**
 * @brief 
 * 
 * @param file 
 * @param inode 
 * @param group 
 * @param super 
 * @param file_name 
 */
void catCommand(FILE* file, struct ext2_inode inode, struct ext2_group_desc *group, struct ext2_super_block* super, char* file_name);
