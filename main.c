#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include "utils/utils.h"
#include "commands/help/help.h"
#include "commands/info/info.h"
#include "commands/cat/cat.h"
#include "commands/attr/attr.h"
#include "commands/pwd/pwd.h"
#include "commands/ls/ls.h"
#include "commands/cd/cd.h"


int main(int argc, char **argv){
	if (argc != 2) {
    printf(RED("ERROR:") " Formato de entrada inválido.\n");
    printf("Por favor, utilize o seguinte formato: " BLUE("./main myext2image.img\n"));
    return 0;
 	}

	FILE *file = fopen(argv[1], "rb+");

	if (file == NULL) {
		printf(RED("ERROR:") "Erro ao abrir a imagem\n");
		return 1;
  }

  char buffer[1024];
  memset(buffer, '\0', sizeof(buffer));
  char **commands;

  StackDirectory *stackDirectory = createStackDirectory();

  // initializing superblock struct
	struct ext2_super_block super;

  // reading superblock
	read_super_block(file, &super);
  super.s_log_block_size = BLOCK_SIZE;
  super.s_log_frag_size = BLOCK_SIZE;

  // initializing group descriptor struct
  struct ext2_group_desc gdesc[GROUP_COUNT];

  // reading group descriptor
  read_group_descriptors(file, &super, gdesc);

  // initializing inode strut
  struct ext2_inode inode;

  // initializing dir entry struct
  struct ext2_dir_entry_2 dirEntry;

  read_inode(file, 2, gdesc, &inode, &super);
  read_all_dirs_and_push_into_stack(file, &inode, gdesc, stackDirectory, "/");

  system("clear");
  char *pwd = pwdCommand(stackDirectory);
  printf(GREEN("ext2shell:") BLUE("[%s]") "$ ", pwd);

  while(fgets(buffer, 1024, stdin) != NULL){
    int amountOfCommands = tokenize_array_of_commands(&commands, buffer, &amountOfCommands);

    if (*commands != NULL) {
      if (!strcmp(commands[0], "ls")) {
        if(amountOfCommands > 1) {
          printf(RED("ERROR: ") "Quantidade de argumentos inválidos para o comando" GREEN(" ls")"\n");
        }else {
          lsCommand(stackDirectory->currentDirectory->listDirEntry);
        }
      } else if (!strcmp(commands[0], "cd")) {
        if (amountOfCommands != 2) {
          printf(RED("ERROR: ") "Quantidade de argumentos inválidos para o comando" GREEN(" cd") "\n");
        } else {
          if(!commands[1]) {
            printf(RED("ERROR: ") "Quantidade de argumentos inválidos para o comando" GREEN(" cd") "\n");
          } else {
            cdCommand(file, gdesc, stackDirectory, &super, commands[1]);
          }
        }
      } else if (!strcmp(commands[0], "info")) {
        if(amountOfCommands > 1){
          printf(RED("ERROR: ") "Quantidade de argumentos inválidos para o comando" GREEN(" info")"\n");
        }else {
          infoCommand(&super);
        }
      } else if (!strcmp(commands[0], "pwd")) {
        if(amountOfCommands > 1){
          printf(RED("ERROR: ") "Quantidade de argumentos inválidos para o comando" GREEN(" pwd")"\n");
        }else {
          printf("%s\n", pwd);
        }
      } else if (!strcmp(commands[0], "attr")) {
        if (amountOfCommands < 2) {
          printf("Quantidade de argumentos inválidos para o comando attr.\n");
        } else {
          if(amountOfCommands > 2){
            char file_name[255];
            for(int i = 1; i < amountOfCommands; i++){
              strcat(file_name, commands[i]);
              if(i < amountOfCommands - 1){
                strcat(file_name, " ");
              }
            }
            attrCommand(file, inode, stackDirectory, gdesc, &super, file_name);
            memset(file_name, 0, 255);
          }else {
            attrCommand(file, inode, stackDirectory, gdesc, &super, commands[1]);
          }
        }
      } else if (!strcmp(commands[0], "cat")) {
        if (amountOfCommands < 2) {
          printf("Quantidade de argumentos inválidos para o comando cat.\n");
        } else {
          if(amountOfCommands > 2){
            char file_name[255];
            for(int i = 1; i < amountOfCommands; i++){
              strcat(file_name, commands[i]);
              if(i < amountOfCommands - 1){
                strcat(file_name, " ");
              }
            }
            catCommand(file, inode, stackDirectory, gdesc, &super, file_name);
            memset(file_name, 0, 255);
          }else {
            catCommand(file, inode, stackDirectory, gdesc, &super, commands[1]);
          }
        }
      } else if (!strcmp(commands[0], "clear")) {
        system("clear");
      } else if (!strcmp(commands[0], "help")) {
        helpCommand();
      } else if (!strcmp(commands[0], "exit")) {
        break;
      } else if(!strcmp(commands[0], "print")){
        if (amountOfCommands < 2) {
          printf("Quantidade de argumentos inválidos para o comando print.\n");
        }
        if(!strcmp(commands[1], "superblock")){
	        print_super_block(&super, BLOCK_SIZE);
        } else if(!strcmp(commands[1], "groups")){
          for(int i = 0; i < get_amount_groups_in_block(&super); i++){
            print_group_descriptor(gdesc[i], i);
          }
        } else if(!strcmp(commands[1], "inode")){
          if(amountOfCommands != 3){
            printf("Quantidade de argumentos inválidos para o comando print inode.\n");
            printf("Exemplo: " BLUE("print inode 2") "\n");
          } else{
            read_inode(file, atoi(commands[2]), gdesc, &inode, &super); 
            print_inode(&inode);
          }
        }
      } else {
        printf(RED("[Comando Inválido]") ": Digite " BLUE(
            "help") " para ver as opções disponíveis.\n");
      }
    }

    // fclose(file);
    // file = fopen("myimagefat32.img", "rb+");

    destroy_array_of_commands(commands, amountOfCommands);

    free(pwd);
    pwd = pwdCommand(stackDirectory);
    printf(GREEN("ext2shell:") BLUE("[%s]") "$ ", pwd);
  }

  printf("\n");
  fclose(file);
  destroyStack(stackDirectory);

	return 0;
}