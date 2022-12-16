/**
 * @file ls.c
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de declaração da função que realiza o comando ls
 * @version 0.1
 * @date 2022-12-16
 * 
 * 
 */

#pragma once

#include "../../EXT2/ext2.h"
#include "../../utils/utils.h"


/**
 * @brief função que realiza o comando ls
 * 
 * @param inode 
 * @param group 
 */
void lsCommand(struct ext2_inode inode, struct ext2_group_desc *group);