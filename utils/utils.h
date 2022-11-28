#pragma once

#include <stdio.h>
#include <inttypes.h>

#include "../ext2/ext2.h"

#define BASE_OFFSET 1024  /* location of the super-block in the first group */
#define BLOCK_OFFSET(block) (BASE_OFFSET + (block-1)*block_size)

// COLORS
#define BLUE(string) "\x1b[34m" string "\x1b[0m"
#define RED(string) "\x1b[31m" string "\x1b[0m"
#define GREEN(string) "\x1B[32m" string "\x1b[0m"
#define YELLOW(string) "\x1B[33m" string "\x1b[0m"
#define CYAN(string) "\x1B[36m" string "\x1b[0m"

void print_super_block(struct ext2_super_block super, unsigned int block_size);
void print_group_descriptor(struct ext2_super_block super, unsigned int block_size);