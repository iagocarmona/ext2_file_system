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

#include "../../EXT2/ext2.h"
#include "../../utils/utils.h"

/**
 * @brief exibe atributos de um arquivo ou diretório
 * 
 * @param file imagem do sistema 
 * @param inode 
 * @param group Fescritor de Grupo de Blocos
 * @param super superbloco
 * @param file_name nome do arquivo
 */
void attrCommand(FILE* file, struct ext2_inode inode, struct ext2_group_desc *group, struct ext2_super_block* super, char* file_name);
