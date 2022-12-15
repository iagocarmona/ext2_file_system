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

#define BASE_OFFSET 1024  /* localização do super bloco no primeiro grupo */
#define GROUP_COUNT 8 /* contador de grupos */
#define BLOCK_SIZE 1024
#define BLOCK_OFFSET(block) (BASE_OFFSET + (block-1)*BASE_OFFSET)

/* cores */
#define BLUE(string) "\x1b[34m" string "\x1b[0m"
#define RED(string) "\x1b[31m" string "\x1b[0m"
#define GREEN(string) "\x1B[32m" string "\x1b[0m"
#define YELLOW(string) "\x1B[33m" string "\x1b[0m"
#define CYAN(string) "\x1B[36m" string "\x1b[0m"

/**
 * @brief lê o superbloco do arquivo
 * 
 * @param file o ponteiro de arquivo da onde será lido
 * @param super a estrutura do superbloco onde estão armazenada as informações do sistema
 */
void read_super_block(FILE* file, struct ext2_super_block* super);



/**
 * @brief lề as informações presentes na Descritor de Grupo
 * 
 * @param file arquivo de onde será lido
 * @param super a estrutura de superbloco
 * @param gdesc array de descritores de grupo
 */
void read_group_descriptors(FILE* file, struct ext2_super_block* super, struct ext2_group_desc* gdesc);



/**
 * @brief lê as informações presentes na estrutura de inode
 * 
 * @param file arquivo de onde os dados serão lidos
 * @param inode_no o número do inode
 * @param gdesc descritor de grupo do inode
 * @param inode estrutura do inode que será lido
 * @param super estrutura do superbloco
 */
void read_inode(FILE* file, int inode_no, struct ext2_group_desc* gdesc,  struct ext2_inode* inode, struct ext2_super_block* super);



/**
 * @brief tokenize a string passada como parâmetro em um array de strings
 * 
 * @param commands ponteiro para um vetor de ponteiros de string
 * @param arg a string que será tokenizada
 * @param amountOfCommands a quantidade de comandaos a serem armazenados no array
 * @return int a quantidade de comandos
 */
int tokenize_array_of_commands(char ***commands, char *arg, int *amountOfCommands);




/**
 * @brief libera o vetor de de string
 * 
 * @param commands o vetor de string que será liberado
 * @param amountOfCommands a quantidade de comando no vetor
 */
void destroy_array_of_commands(char **commands, int amountOfCommands);




/**
 * @brief 
 * 
 * @param super 
 * @param block_size 
 */
void print_super_block(struct ext2_super_block* super, unsigned int block_size);



/**
 * @brief 
 * 
 * @param gdesc 
 * @param i 
 */
void print_group_descriptor(struct ext2_group_desc gdesc, int i);



/**
 * @brief 
 * 
 * @param inode 
 */
void print_inode(struct ext2_inode* inode);



/**
 * @brief função que calcula o número de grupo de dado inode
 * 
 * @param super estrutura de superbloco
 * @param inode_no número do inode
 * @return int - número de grupo do inode
 */
int get_inode_group(struct ext2_super_block* super, int inode_no);




/**
 * @brief função que calcula o número de inodes por bloco
 * 
 * @param super estrura do superbloco que contém as informações necessáris
 * @return int - número de inodes por bloco
 */
int get_inodes_per_block(struct ext2_super_block* super);



/**
 * @brief Get the amount groups in block object
 * 
 * @param super 
 * @return int 
 */
int get_amount_groups_in_block(struct ext2_super_block* super);



/**
 * @brief Get the amount inodes in itable object
 * 
 * @param super 
 * @return int 
 */
int get_amount_inodes_in_itable(struct ext2_super_block* super);



/**
 * @brief Get the offset of inode in itable object
 * 
 * @param super 
 * @param gdesc 
 * @param inode_no 
 * @return int 
 */
int get_offset_of_inode_in_itable(struct ext2_super_block* super, struct ext2_group_desc* gdesc, int inode_no);



/**
 * @brief 
 * 
 * @param file 
 * @param inode 
 * @param group 
 */
void read_all_root_dirs(FILE* file, struct ext2_inode *inode, struct ext2_group_desc *group);



/**
 * @brief 
 * 
 * @param file 
 * @param inode 
 * @param group 
 * @param nomeArquivo 
 * @return uint32_t 
 */
uint32_t read_dir(FILE* file, struct ext2_inode *inode, struct ext2_group_desc *group, char* nomeArquivo);



/**
 * @brief 
 * 
 * @param time 
 * @return char* 
 */
char* convertNumToUnixTime(uint32_t time);