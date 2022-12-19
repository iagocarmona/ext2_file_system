/**
 * @file attr.h
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de declaração da função usada para o comando attr
 * 
 * Data de criação: 28/11/2022
 * Datas de modificações: 09/12/2022, 15/12/2022, 17/12/2022
 *  
 */


#pragma once

#include "../../utils/utils.h"

/**
 * @brief exibe atributos de um arquivo ou diretório
 * 
 * @param file imagem do sistema
 * @param inode 
 * @param stack ílha de diretórios
 * @param group Descritor de Grupo de Blocos
 * @param super Superbloco
 * @param file_name nome do arquivo
 */
void attrCommand(FILE* file, Inode inode, StackDirectory* stack, GroupDescriptor *group, Superblock* super, char* file_name);