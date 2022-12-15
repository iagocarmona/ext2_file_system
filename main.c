#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include "EXT2/ext2.h"
#include "utils/utils.h"
#include "StackDirectory/stackDirectory.h"
#include "commands/help/help.h"
#include "commands/info/info.h"
#include "commands/cat/cat.h"
#include "commands/attr/attr.h"


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
  memset(buffer, '\0', sizeof(buffer)); /* reseta */
  char **commands;

  struct StackDirectory *stackDirectory = createStackDirectory(); /* cria estrtura de pilha de diretório */

  /* incializando estrutura do superbloco */ 
	struct ext2_super_block super;

  /* lendo superbloco */ 
	read_super_block(file, &super);
  super.s_log_block_size = BLOCK_SIZE;
  super.s_log_frag_size = BLOCK_SIZE;

  /* incializando estrutura do descritor de grupo */
  struct ext2_group_desc gdesc[GROUP_COUNT];

  /* lendo descritor de grupo */
  read_group_descriptors(file, &super, gdesc);

  /* inicializando estrutura inode */
  struct ext2_inode inode;

  /* inicializando estrutura do diretório de entrada */
  struct ext2_dir_entry_2 dirEntry;

  read_inode(file, 2, gdesc, &inode, &super);
  read_all_root_dirs(file, &inode, gdesc);

  // system("clear");
  // char *pwd = pwdCommand(stackDirectory);
  printf(GREEN("ext2shell:") BLUE("[/]") "$ ");

  while(fgets(buffer, 1024, stdin) != NULL){
    int amountOfCommands = tokenize_array_of_commands(&commands, buffer, &amountOfCommands);

    if (*commands != NULL) {
      if (!strcmp(commands[0], "ls")) {
        // lsCommand(stackDirectory->currentDirectory->listDirEntry);
      } else if (!strcmp(commands[0], "cd")) {
        if (amountOfCommands != 2) {
          printf("Quantidade de argumentos inválidos para o comando cd.\n");
        } else {
          // cdCommand(fat1, bootSector, stackDirectory, file, commands[1]);
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
        // printf("%s\n", pwd);
      } else if (!strcmp(commands[0], "attr")) {
        if (amountOfCommands != 2) {
          printf("Quantidade de argumentos inválidos para o comando attr.\n");
        } else {
          attrCommand(file, inode, gdesc, &super, commands[1]);
        }
      } else if (!strcmp(commands[0], "cat")) {
        if (amountOfCommands != 2) {
          printf(
              "Quantidade de argumentos inválidos para o comando cat.\n");
        } else {
          catCommand(file, inode, gdesc, &super, commands[1]);
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

    // destroy_array_of_commands(commands, amountOfCommands);
    printf(GREEN("ext2shell:") BLUE("[/]") "$ ");
  }

  printf("\n");
  fclose(file);

	return 0;
}