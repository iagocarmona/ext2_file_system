#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include "ext2/ext2.h"
#include "utils/utils.h"

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

	struct ext2_super_block super;

	fseek(file, 1024, SEEK_CUR);
  	fread(&super, sizeof(ext2_super_block), 1, file);

	unsigned int block_size = 1024 << super.s_log_block_size;   /* block size in bytes */

	system("clear");

	print_super_block(super, block_size);

	return 0;
}