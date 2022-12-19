/**
 * @file cat.h
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de declaração de função que executa o comando cat
 * 
 * Data de criação: 28/11/2022
 * Datas de modificações: 09/12/2022, 15/12/2022, 17/12/2022
 * 
 */

#pragma once

#include "../../EXT2/ext2.h"
#include "../../utils/utils.h"


/**
 * @brief função que exxeuta o comando cat
 * 
 * @param file sistema de arquivos
 * @param inode 
 * @param stack pilha de diretórios
 * @param group Descritor de Grupos de Blocos
 * @param super Superblobo
 * @param file_name nome do arquivo que terá conteúdo lido
 */
void catCommand(FILE* file, Inode inode, StackDirectory* stack, GroupDescriptor *group, Superblock* super, char* file_name);