#pragma once

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include "../EXT2/ext2.h"
#include "../ListDirEntry/listDirEntry.h"
#include "../StackDirectory/stackDirectory.h"

#define BASE_OFFSET 1024  /* location of the super-block in the first group */
#define GROUP_COUNT 8
#define BLOCK_SIZE 1024
#define BLOCK_OFFSET(block) (BASE_OFFSET + (block-1)*BASE_OFFSET)

// COLORS
#define BLUE(string) "\x1b[34m" string "\x1b[0m"
#define RED(string) "\x1b[31m" string "\x1b[0m"
#define GREEN(string) "\x1B[32m" string "\x1b[0m"
#define YELLOW(string) "\x1B[33m" string "\x1b[0m"
#define CYAN(string) "\x1B[36m" string "\x1b[0m"

void read_super_block(FILE* file, Superblock* super);
void read_group_descriptors(FILE* file, Superblock* super, GroupDescriptor* gdesc);
void read_inode(FILE* file, int inode_no, GroupDescriptor* gdesc,  Inode* inode, Superblock* super);
int tokenize_array_of_commands(char ***commands, char *arg, int *amountOfCommands);
void destroy_array_of_commands(char **commands, int amountOfCommands);
void print_super_block(Superblock* super, unsigned int block_size);
void print_group_descriptor(GroupDescriptor gdesc, int i);
void print_inode(Inode* inode);
int get_inode_group(Superblock* super, int inode_no);
int get_inodes_per_block(Superblock* super);
int get_amount_groups_in_block(Superblock* super);
int get_amount_inodes_in_itable(Superblock* super);
int get_offset_of_inode_in_itable(Superblock* super, GroupDescriptor* gdesc, int inode_no);
void read_all_root_dirs(FILE* file, Inode* inode, GroupDescriptor* group, StackDirectory* stackDirectory, char* name);
uint32_t read_dir(FILE* file, Inode *inode, GroupDescriptor *group, char* nomeArquivo);
char* convertNumToUnixTime(uint32_t time);