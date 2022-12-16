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
