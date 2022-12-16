/**
 * @file ls.c
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de implementaçã da função que realiza o comando ls
 * @version 0.1
 * @date 2022-12-16
 * 
 * 
 */

#include "ls.h"

void lsCommand(struct ext2_inode inode, struct ext2_group_desc *group){
    
    uint32_t len; /* variável de tamnho do inode */

    if(inode.i_mode & 0x4000){ /* verifica se inode é de tipo diretório */
        len = 0; /* variável de tamanho do inode */
    }

    while(len < inode.i_size){ /* enquanto não exceder o tamanho */

    }
}