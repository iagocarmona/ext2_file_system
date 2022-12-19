/**
 * @file pwd.h
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de declaração da função que executa o comando pwd
 * 
 * Data de criação: 28/11/2022
 * Datas de modificações: 07/12/022
 * 
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../StackDirectory/stackDirectory.h"

/**
 * @brief função que irá executar o comando pwd
 * 
 * @param stackDirectory 
 * @return char* 
 */
char* pwdCommand(StackDirectory* stackDirectory);