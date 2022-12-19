/**
 * @file cd.h
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginal Gregorio de Souza Neto
 * @brief arquivo de declaração da função que executa o comando cd
 * 
 * Data de criação: 28/11/2022
 * Datas de modificações: 07/12/2022, 17/12/2022
 * 
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../utils/utils.h"
#include "../pwd/pwd.h"

/**
 * @brief função que realiza o comando cd
 * 
 * @param file imagem do sistema de arquivos
 * @param group Descritor de Grupo de Blocos
 * @param stack pilha de diretórios
 * @param super Superbloco
 * @param path caminho que quer acessar
 * @return int 
 */
int cdCommand(FILE* file, GroupDescriptor *group, StackDirectory* stack, Superblock* super, char* path);