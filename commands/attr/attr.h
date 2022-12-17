/**
 * @file attr.h
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de declaração da função usada para o comando attr
 * @version 0.4
 * @date 2022-11-15
 *  
 */


#pragma once

#include "../../utils/utils.h"

/**
 * @brief exibe atributos de um arquivo ou diretório
 * 
 * @param file imagem do sistema 
 * @param inode 
 * @param group Descritor de Grupo de Blocos
 * @param super Superbloco
 * @param file_name nome do arquivo
 */
void attrCommand(FILE* file, Inode inode, StackDirectory* stack, GroupDescriptor *group, Superblock* super, char* file_name);
