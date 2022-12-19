/**
 * @file info.h
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de declaração da função usada para o comando info
 * 
 * Data de criação: 28/11/2022
 * Datas de modificações: 07/12/022
 * 
 */

#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "../../EXT2/ext2.h"

/**
 * @brief função que por meio do parâmetro recebido irá exibir as informações referentes
 * ao disco e ao sistema de arquivos
 * 
 * @param super estrutura de dados do superbloco na qual é armazenada as informaçõe do sistema
 */
void infoCommand(struct ext2_super_block* super);