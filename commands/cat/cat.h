#pragma once

#include "../../EXT2/ext2.h"
#include "../../utils/utils.h"

void catCommand(FILE* file, Inode inode, StackDirectory* stack, GroupDescriptor *group, Superblock* super, char* file_name);
