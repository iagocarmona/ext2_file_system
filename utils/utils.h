/**
 * @file utils.h
 * @author Iago Ortega Carmona
 * @author Thiago Griani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de declaração de funções recorrentes na implementação
 * 
 * Data de criação: 27/11/2022
 * Datas de modificação: 28/11/2022, 01/12/2022, 07/12/2022, 09/12/2022, 16/12/2022,
 * 17/12/2022
 * 
 */

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

#define BASE_OFFSET 1024  /* Localização do superblock no primeiro descritor de grupo. */
#define GROUP_COUNT 8
#define BLOCK_SIZE 1024
#define BLOCK_OFFSET(block) (BASE_OFFSET + (block-1)*BASE_OFFSET)

// COLORS
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
void read_super_block(FILE* file, Superblock* super);

/**
 * @brief lề as informações presentes na Descritor de Grupo
 * 
 * @param file imagem do sistema de arquivos
 * @param super a estrutura de superbloco
 * @param gdesc array de descritores de grupo
 */
void read_group_descriptors(FILE* file, Superblock* super, GroupDescriptor* gdesc);

/**
 * @brief lê as informações presentes na estrutura de inode
 * 
 * @param file imagem do sistema de arquivos
 * @param inode_no o número do inode
 * @param gdesc descritor de grupo do inode
 * @param inode estrutura do inode que será lido
 * @param super estrutura do superbloco
 */
void read_inode(FILE* file, int inode_no, GroupDescriptor* gdesc,  Inode* inode, Superblock* super);

/**
 * @brief tokenize a string passada como parâmetro em um array de strings
 * 
 * @param commands ponteiro para um vetor de ponteiros de string
 * @param arg a string que será tokenizada
 * @param amountOfCommands a quantidade de comandaos a serem armazenados no array
 * @return int a quantidade de caracteres
 */
int tokenize_array_of_commands(char ***commands, char *arg, int *amountOfCommands);

/**
 * @brief libera o vetor de string
 * 
 * @param commands o vetor de string que será liberado
 * @param amountOfCommands a quantidade de comando no vetor
 */
void destroy_array_of_commands(char **commands, int amountOfCommands);

/**
 * @brief função que irá exibir as informações armazenadas na estrutura do superbloco
 * 
 * @param super estrutura na qual as informações estão guardadas
 * @param block_size tamnho do bloco
 */
void print_super_block(Superblock* super, unsigned int block_size);

/**
 * @brief função que irá exibir as informações armazenadas na estrutura do Descritor de Grupo de Blocos
 * 
 * @param gdesc estrutura na qual as informações estão guardadas
 * @param i número do desritor do grupo de blocos
 */
void print_group_descriptor(GroupDescriptor gdesc, int i);

/**
 * @brief função que irá exibir as informações armazenadas no inode
 * 
 * @param inode estrutura na qual as informações estão guardadas
 */
void print_inode(Inode* inode);

/**
 * @brief função que calcula o número do descritor de grupo de um dado inode
 * 
 * @param super estrutura de superbloco
 * @param inode_no número do inode
 * @return int - número de grupo do inode
 */
int get_inode_group(Superblock* super, int inode_no);

/**
 * @brief função que calcula o número de inodes por bloco
 * 
 * @param super estrura do superbloco que contém as informações necessárias
 * @return int - número de inodes por bloco
 */
int get_inodes_per_block(Superblock* super);

/**
 * @brief função que calcula a quantidade de grupos no bloco
 * 
 * @param super estrura do superbloco que contém as informações necessárias
 * @return int - número de grupos no bloco
 */
int get_amount_groups_in_block(Superblock* super);

/**
 * @brief retorna o número de inodes da tabela de inodes
 * 
 * @param super estrutura que contém as informações necessárias para a função
 * @return int - número de inodes da tabela de inodes
 */
int get_amount_inodes_in_itable(Superblock* super);

/**
 * @brief retorna o offset de um inode da tabela de inode
 * 
 * @param super estrutura do superbloco
 * @param gdesc estrutura do Descritor do Grupo de Blocos
 * @param inode_no número do inode
 * @return int - offset de um inode da tabela de inode
 */
int get_offset_of_inode_in_itable(Superblock* super, GroupDescriptor* gdesc, int inode_no);

/**
 * @brief lê os diretórios presentes e colocam todos eles na lista de DirEntry dentro da pilha do diretório atual.
 * 
 * @param file imagem do sistema
 * @param inode 
 * @param group Descritor de Grupo de Blocos
 * @param stackDirectory pilha de diretórios
 * @param name noe do arquivo
 */
void read_all_dirs_and_push_into_stack(FILE* file, Inode* inode, GroupDescriptor* group, StackDirectory* stackDirectory, char* name);

/**
 * @brief função que procura o arquivo com o nome passado como parâmetro
 * 
 * @param file imagem do sistema
 * @param inode 
 * @param group Descritor de Grupo de Blocos
 * @param nomeArquivo 
 * @return uint32_t 
 */
uint32_t read_dir(FILE* file, Inode *inode, GroupDescriptor *group, char* nomeArquivo);

/**
 * @brief converte número para o tempo UNIX
 * 
 * @param time número que será convertido
 * @return char* ponteiro para o vetor de string contendo a hora formatada
 */
char* convert_num_to_unix_time(uint32_t time);