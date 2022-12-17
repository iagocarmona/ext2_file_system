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
        lsCommand(stackDirectory->currentDirectory->listDirEntry);
      } else if (!strcmp(commands[0], "cd")) {
        if (amountOfCommands != 2) {
          printf("Quantidade de argumentos inválidos para o comando cd.\n");
        } else {
          cdCommand(file, gdesc, stackDirectory, &super, commands[1]);
        }
      } else if (!strcmp(commands[0], "info")) {
        infoCommand(&super);
      } else if (!strcmp(commands[0], "touch")) {
        if (amountOfCommands != 2) {
          printf("Quantidade de argumentos inválidos para o comando touch.\n");
        } else {
          // touchCommand(fat1, &fsInfo, bootSector, file,
          //              stackDirectory->currentDirectory->listDirEntry,
          //              commands[1]);
        }
      } else if (!strcmp(commands[0], "rm")) {
        if (amountOfCommands != 2) {
          printf("Quantidade de argumentos inválidos para o comando rm.\n");
        } else {
          // rmCommand(stackDirectory->currentDirectory->listDirEntry, commands[1],
          //           file, fat1, bootSector, &fsInfo);
        }
      } else if (!strcmp(commands[0], "cp")) {
        if (amountOfCommands != 3) {
          printf("Quantidade de argumentos inválidos para o comando cp.\n");
        } else {
          // cpCommand(stackDirectory, file, fat1, bootSector, &fsInfo,
          //           commands[1], commands[2]);
        }
      } else if (!strcmp(commands[0], "pwd")) {
        printf("%s\n", pwd);
      } else if (!strcmp(commands[0], "attr")) {
        if (amountOfCommands != 2) {
          printf("Quantidade de argumentos inválidos para o comando attr.\n");
        } else {
          attrCommand(file, inode, stackDirectory, gdesc, &super, commands[1]);
        }
      } else if (!strcmp(commands[0], "cat")) {
        if (amountOfCommands != 2) {
          printf(
              "Quantidade de argumentos inválidos para o comando cat.\n");
        } else {
          catCommand(file, inode, stackDirectory, gdesc, &super, commands[1]);
        }
      } else if (!strcmp(commands[0], "rename")) {
        if (amountOfCommands != 3) {
          printf("Quantidade de argumentos inválidos para o comando rename.\n");
        } else {
          // renameCommand(bootSector, file,
          //               stackDirectory->currentDirectory->listDirEntry,
          //               commands[1], commands[2]);
        }
      } else if (!strcmp(commands[0], "mv")) {
        if (amountOfCommands != 3) {
          printf("Quantidade de argumentos inválidos para o comando mv.\n");
        } else {
          // mvCommand(stackDirectory, file, fat1, bootSector, &fsInfo,
          //           commands[1], commands[2]);
        }
      } else if (!strcmp(commands[0], "mkdir")) {
        if (amountOfCommands != 2) {
          printf("Quantidade de argumentos inválidos para o comando mkdir.\n");
        } else {
          // mkdirCommand(fat1, &fsInfo, bootSector, file,
          //              stackDirectory->currentDirectory->listDirEntry,
          //              stackDirectory, commands[1]);
        }
      } else if (!strcmp(commands[0], "rmdir")) {
        if (amountOfCommands != 2) {
          printf("Quantidade de argumentos inválidos para o comando rmdir.\n");
        } else {
          // rmdirCommand(stackDirectory, commands[1], file, fat1, bootSector,
          //              &fsInfo);
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