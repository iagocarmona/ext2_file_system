#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "../../EXT2/ext2.h"

/**
 * @brief função que por meio do parâmetro recebido irá exibir as informações referentes
 * ao disco e ao sistema de arquivos
 * 
 * @param super estrutura de dados (superbloco) na qual é armazenada as informaçõe do sistema
 */
void infoCommand(struct ext2_super_block* super);