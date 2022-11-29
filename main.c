#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include "ext2/ext2.h"
#include "utils/utils.h"
#include "commands/help/help.h"

#define GROUP_COUNT 8
#define BLOCK_OFFSET(block, block_size) (BASE_OFFSET + (block-1)*block_size)

int tokenizeArrayOfCommands(char ***commands, char *arg, int *amountOfCommands) {
  int size = strlen(arg);

  if (size < 1) return -1;

  char argsTokenized[size];
  memset(argsTokenized, '\0', size);
  strcpy(argsTokenized, arg);
  argsTokenized[size - 1] = '\0';

  // Contando quantas strings devemos armazenar
  int amountOfStrings = 1;
  char *token = strchr(argsTokenized, ' ');
  while (token != NULL) {
    amountOfStrings++;
    token++;
    token = strchr(token, ' ');
  }

  char **tokenizedCommands = (char **)calloc(amountOfStrings, sizeof(char *));
  int i = 0;
  token = strtok(argsTokenized, " ");
  char *buffer;

  while (token != 0x0) {
    buffer = (char *)calloc(strlen(token) + 1, sizeof(char));
    strcpy(buffer, token);
    tokenizedCommands[i++] = buffer;
    token = strtok(NULL, " ");
  }

  *commands = tokenizedCommands;
  return amountOfStrings;
}

void destroyArrayOfCommands(char **commands, int amountOfCommands) {
  for (int i = 0; i < amountOfCommands; i++) {
    free(commands[i]);
  }

  free(commands);
}

static void read_super_block(FILE* file, struct ext2_super_block* super){
  fseek(file, 1024, SEEK_SET);
  fread(super, sizeof(ext2_super_block), 1, file);
}

static void read_group_descriptors(FILE* file, int block_size, int group_count, struct ext2_group_desc* gdesc){
  fseek(file, 1024 + block_size, SEEK_SET);
  for(int i = 0; i < group_count; i++){
    fread(&gdesc[i], sizeof(ext2_group_desc), 1, file);
  }
}

static void read_inode(FILE* file, int inode_no, struct ext2_group_desc* gdesc,  struct ext2_inode* inode, int block_size, int inode_in_group){
  int offset = BLOCK_OFFSET(gdesc[inode_in_group].bg_inode_table, block_size)+(inode_no-1)*sizeof(struct ext2_inode);
	fseek(file, offset, SEEK_SET);
  fread(inode, sizeof(ext2_inode), 1, file);
}

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

  // initializing superblock struct
	struct ext2_super_block super;

  // reading superblock
	read_super_block(file, &super);

  /* block size in bytes */
	unsigned int block_size = 1024 << super.s_log_block_size;   

  /* calculate number of block groups on the disk */
  int group_count = 1 + (super.s_blocks_count-1) / super.s_blocks_per_group;

  // initializing group descriptor struct
  struct ext2_group_desc gdesc[GROUP_COUNT];

  // reading group descriptor
  read_group_descriptors(file, block_size, group_count, gdesc);

  /* number of inodes per block */
  unsigned int inodes_per_block = block_size / sizeof(struct ext2_inode);

  /* size in blocks of the inode table */
  unsigned int itable_blocks = super.s_inodes_per_group / inodes_per_block;

  // initializing inode strut
  struct ext2_inode inode;

  // system("clear");
  // char *pwd = pwdCommand(stackDirectory);
  // printf(GREEN("ext2shell:") BLUE("[myext2image/] %s ") "$ ", pwd);

  while(fgets(buffer, 1024, stdin) != NULL){
    int amountOfCommands = tokenizeArrayOfCommands(&commands, buffer, &amountOfCommands);

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
        // infoCommand(file, bootSector, fat1, &fsInfo);
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
          // attrCommand(stackDirectory->currentDirectory->listDirEntry,
          //             commands[1]);
        }
      } else if (!strcmp(commands[0], "cat")) {
        if (amountOfCommands != 2) {
          printf(
              "Quantidade de argumentos inválidos para o comando cluster.\n");
        } else {
          // cluster(bootSector, file, atoi(commands[1]));
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
	        print_super_block(super, block_size);
        } else if(!strcmp(commands[1], "groups")){
          for(int i = 0; i < group_count; i++){
            print_group_descriptor(gdesc[i], i);
          }
        } else if(!strcmp(commands[1], "inode")){
          if(amountOfCommands != 3){
            printf("Quantidade de argumentos inválidos para o comando print inode.\n");
            printf("Exemplo:" BLUE("print inode 2") "\n");
          } else{
            int inode_no = atoi(commands[2]);
            int inodes_per_group = super.s_inodes_per_group;
            int inode_in_group = inode_no / inodes_per_group;
            read_inode(file, atoi(commands[2]), gdesc, &inode, block_size, inode_in_group); 
            print_inode(inode);
          }
        }
      } else {
        printf(RED("[Comando Inválido]") ": Digite " BLUE(
            "help") " para ver as opções disponíveis.\n");
      }
    }
  }

  printf("\n\n");

	return 0;
}