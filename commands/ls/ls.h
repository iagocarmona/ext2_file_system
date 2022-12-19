/**
 * @file ls.h
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de declaração da função que realiza o comando ls
 * 
 * Data de criação: 28/11/2022
 * 
 */


#pragma once

#include "../../utils/utils.h"

/**
 * @brief função que realiza a execução do comando ls
 * 
 * @param listDirEntry lista de entradas de diretórios
 */
void lsCommand(ListDirEntry *listDirEntry);