/**
 * @file cd.h
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author 
 * @brief 
 * @version 0.1
 * @date 2022-12-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../StackDirectory/stackDirectory.h"
#include "../../utils/utils.h"
#include "../pwd/pwd.h"

/**
 * @brief função que realiza o comando cp <path>
 * 
 * @param file 
 * @param inode 
 * @param group 
 * @param nomeArquivo 
 */
void cdCommand(FILE* file, struct ext2_inode *inode, struct ext2_group_desc *group, char* nomeArquivo);