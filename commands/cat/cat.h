/**
 * @file cat.h
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de declaração de função que executa o comando cat
 * @version 0.1
 * @date 2022-12-17
 * 
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