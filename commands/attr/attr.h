#pragma once

#include "../../utils/utils.h"

void attrCommand(FILE* file, struct ext2_inode inode, struct ext2_group_desc *group, struct ext2_super_block* super, char* file_name);
