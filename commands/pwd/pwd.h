/**
 * @file pwd.h
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de declaração da função que realiza o comando pwd
 * @version 0.1
 * @date 2022-12-16
 * 
 *
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../StackDirectory/stackDirectory.h"

/**
 * @brief função que realiza a execução do comando pwd, que exibe o caminho absoluto
 * 
 * @param stackDirectory pilha de diretórios
 * @return char* 
 */
char* pwdCommand(StackDirectory* stackDirectory);