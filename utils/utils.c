/**
 * @file utils.c
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * @brief arquivo de implementação das funções recorrente de uso
 * @version 0.1
 * @date 2022-12-17
 * 
 * 
 */

#include "utils.h"

void read_super_block(FILE* file, Superblock* super){
  fseek(file, 1024, SEEK_SET); /* desloca ponteiro para a posição do superbloco */
  fread(super, sizeof(Superblock), 1, file); /* lê os dados apontado por "file" e os armazenado em "super" */
}

void read_group_descriptors(FILE* file, Superblock* super, GroupDescriptor* gdesc){
  fseek(file, 1024 + super->s_log_block_size, SEEK_SET); /* desloca ponteiro da imagem do sistema de arquivos */
  for(int i = 0; i < get_amount_groups_in_block(super); i++){
    fread(&gdesc[i], sizeof(GroupDescriptor), 1, file); /* lê todos os Descritores de Grupo */
  }
}

void read_inode(FILE* file, int inode_no, GroupDescriptor* gdesc,  Inode* inode, Superblock* super){
	int offset = get_offset_of_inode_in_itable(super, gdesc, inode_no); /* pega offset de inode relacionado ao seu número */
	fseek(file, offset, SEEK_SET); /* desloca ponteiro da imagem de disco */
	fread(inode, sizeof(Inode), 1, file); /* lê a informação a partir do ponteiro */
}

int tokenize_array_of_commands(char ***commands, char *arg, int *amountOfCommands) {
  int size = strlen(arg); /* tamanho da string */

  if (size < 1) return -1;

  char argsTokenized[size];
  memset(argsTokenized, '\0', size);
  strcpy(argsTokenized, arg); /* copia para argsTokenized o conteúdo de arg */
  argsTokenized[size - 1] = '\0';

  // Contando quantas strings devemos armazenar
  int amountOfStrings = 1;
  char *token = strchr(argsTokenized, ' ');
  while (token != NULL) {
    amountOfStrings++;
    token++;
    token = strchr(token, ' ');
  }

  char **tokenizedCommands = (char **)calloc(amountOfStrings, sizeof(char *)); /* aloca espaço para os comandos em forma de tokens */
  int i = 0;
  token = strtok(argsTokenized, " ");
  char *buffer;

  while (token != 0x0) {
    buffer = (char *)calloc(strlen(token) + 1, sizeof(char)); /* aloca buffer com espaço para os tokens */
    strcpy(buffer, token); /* copia o contéudo de token para buffer */
    tokenizedCommands[i++] = buffer;
    token = strtok(NULL, " ");
  }

  *commands = tokenizedCommands; /* commands recebe o cnteúdo de tokenizedCommands */
  return amountOfStrings; /* retorna a quantidade de caracteres */
}

void destroy_array_of_commands(char **commands, int amountOfCommands) {
  for (int i = 0; i < amountOfCommands; i++) {
    free(commands[i]);
  }

  free(commands);
}

void print_super_block(Superblock *super, unsigned int block_size){

	/* acessa e exibe as informações do superbloco a partir da estrutura passa como argumento */

  printf("\n");
	char* s_mtime = convertNumToUnixTime(super->s_mtime);
	char* s_wtime = convertNumToUnixTime(super->s_wtime);
	char* s_lastcheck = convertNumToUnixTime(super->s_lastcheck);

    printf("inodes count.................: %" PRIu32 "\n"
	       "blocks count.................: %" PRIu32 "\n"
	       "reserved blocks count........: %" PRIu32 "\n"
	       "free blocks count............: %" PRIu32 "\n"
	       "free inodes count............: %" PRIu32 "\n"
	       "first data block.............: %" PRIu32 "\n"
	       "block size...................: %" PRIu32 "\n"
	       "fragment size................: %" PRIu32 "\n"
	       "blocks per group.............: %" PRIu32 "\n"
	       "fragments per group..........: %" PRIu32 "\n"
	       "inodes per group.............: %" PRIu32 "\n"
	       "mount time...................: %s\n"
	       "write time...................: %s\n"
	       "mount count..................: %" PRIu16 "\n"
	       "max mount count..............: %" PRIu16 "\n"
	       "magic signature..............: 0x%x\n"
	       "file system state............: %" PRIu16 "\n"
	       "errors.......................: %" PRIu16 "\n"
	       "minor revision level.........: %" PRIu16 "\n"
	       "time of last check...........: %s\n"
	       "max check interval...........: %" PRIu32 "\n"
	       "creator OS...................: %" PRIu32 "\n"
	       "revision level...............: %" PRIu32 "\n"
	       "default uid reserved blocks..: %" PRIu16 "\n"
	       "default gid reserved blocks..: %" PRIu16 "\n"
	       "first non-reserved inode.....: %" PRIu32 "\n"
	       "inode size...................: %" PRIu16 "\n"
	       "block group number...........: %" PRIu16 "\n"
	       "compatible feature set.......: %" PRIu32 "\n"
	       "incompatible feature set.....: %" PRIu32 "\n"
	       "read only comp feature set...: %" PRIu32 "\n"
	       "volume UUID..................: %" PRIu8 "\n"
	       "volume name..................: %s\n"
	       "volume last mounted..........: %s\n"
	       "algorithm usage bitmap.......: %" PRIu32 "\n"
	       "blocks to try to preallocate.: %" PRIu8 "\n"
	       "blocks preallocate dir.......: %" PRIu8 "\n"
	       "journal UUID.................: %" PRIu8 "\n"
	       "journal INum.................: %" PRIu32 "\n"
	       "journal Dev..................: %" PRIu32 "\n"
	       "last orphan..................: %" PRIu32 "\n"
	       "hash seed....................: %" PRIu32 "\n"
	       "default hash version.........: %" PRIu8 "\n"
	       "default mount options........: %" PRIu32 "\n"
	       "first meta...................: %" PRIu32 "\n"
	       ,
	       super->s_inodes_count,  
	       super->s_blocks_count,
	       super->s_r_blocks_count,     /* reserved blocks count */
	       super->s_free_blocks_count,
	       super->s_free_inodes_count,
	       super->s_first_data_block,
	       super->s_log_block_size,
		   super->s_log_frag_size,
	       super->s_blocks_per_group,
		   super->s_frags_per_group,
	       super->s_inodes_per_group,
		   s_mtime,
		   s_wtime,
		   super->s_mnt_count,
		   super->s_max_mnt_count,
		   super->s_magic,
		   super->s_state,
		   super->s_errors,
		   super->s_minor_rev_level,
		   s_lastcheck,
		   super->s_checkinterval,
	       super->s_creator_os,
		   super->s_rev_level,
		   super->s_def_resuid,
		   super->s_def_resgid,
	       super->s_first_ino,         
	       super->s_inode_size,
		   super->s_block_group_nr,
		   super->s_feature_compat,
		   super->s_feature_incompat,
		   super->s_feature_ro_compat,
		   super->s_uuid[0],
		   super->s_volume_name,
		   super->s_last_mounted,
		   super->s_algorithm_usage_bitmap,
		   super->s_prealloc_blocks,
		   super->s_prealloc_dir_blocks,
		   super->s_journal_uuid[0],
		   super->s_journal_inum,
		   super->s_journal_dev,
		   super->s_last_orphan,
		   super->s_hash_seed[0],
		   super->s_def_hash_version,
		   super->s_default_mount_opts,
		   super->s_first_meta_bg);

	printf("\n");
}

void print_group_descriptor(GroupDescriptor gdesc, int i){
  
  /* acessa e exibe as informações do Descritor de Grupo de Blocos a partir da estrutura passa como argumento */

  printf("\n");
	printf("block group descriptor.: %d\n"
		   "block bitmap...........: %" PRIu32 "\n"
		   "inode bitmap...........: %" PRIu32 "\n"
		   "inode table............: %" PRIu32 "\n"
		   "free blocks count......: %" PRIu16 "\n"
		   "free inodes count......: %" PRIu16 "\n"
		   "used dirs count........: %" PRIu16 "\n"
		   ,
		   i,
		   gdesc.bg_block_bitmap,
		   gdesc.bg_inode_bitmap,
		   gdesc.bg_inode_table,
		   gdesc.bg_free_blocks_count,
		   gdesc.bg_free_inodes_count,
		   gdesc.bg_used_dirs_count);
	printf("\n");
}

void print_inode(Inode* inode){

	/* acessa e exibe as informações do inode de Grupo de Blocos a partir da estrutura passa como argumento */

  printf("\n");
  printf("\n");
	printf("file format and access rights....: %" PRIu16 "\n"
	       "user id..........................: %" PRIu16 "\n"
	       "lower 32-bit file size...........: %" PRIu32 "\n"
	       "access time......................: %" PRIu32 "\n"
	       "creation time....................: %" PRIu32 "\n"
	       "modification time................: %" PRIu32 "\n"
	       "deletion time....................: %" PRIu32 "\n"
	       "group id.........................: %" PRIu16 "\n"
	       "link count inode.................: %" PRIu16 "\n"
	       "512-bytes blocks.................: %" PRIu32 "\n"
	       "ext2 flags.......................: %" PRIu32 "\n"
	       "reserved (Linux).................: %" PRIu32 "\n"
	       "pointer[0].......................: %" PRIu32 "\n"
	       "pointer[1].......................: %" PRIu32 "\n"
	       "pointer[2].......................: %" PRIu32 "\n"
	       "pointer[3].......................: %" PRIu32 "\n"
	       "pointer[4].......................: %" PRIu32 "\n"
	       "pointer[5].......................: %" PRIu32 "\n"
	       "pointer[6].......................: %" PRIu32 "\n"
	       "pointer[7].......................: %" PRIu32 "\n"
	       "pointer[8].......................: %" PRIu32 "\n"
	       "pointer[9].......................: %" PRIu32 "\n"
	       "pointer[10]......................: %" PRIu32 "\n"
	       "pointer[11]......................: %" PRIu32 "\n"
	       "pointer[12]......................: %" PRIu32 "\n"
	       "pointer[13]......................: %" PRIu32 "\n"
	       "pointer[14]......................: %" PRIu32 "\n"
	       "file version (nfs)...............: %" PRIu32 "\n"
	       "block number extended attributes.: %" PRIu32 "\n"
	       "higher 32-bit file size..........: %" PRIu32 "\n"
	       "location file fragment...........: %" PRIu32 "\n"
	       ,
	       inode->i_mode,  
	       inode->i_uid,
	       inode->i_size,
		   inode->i_atime,
		   inode->i_ctime,
		   inode->i_mtime,
		   inode->i_dtime,
		   inode->i_gid,
		   inode->i_links_count,
		   inode->i_blocks,
		   inode->i_flags,
		   inode->osd1.linux1.l_i_reserved1,
		   inode->i_block[0],
		   inode->i_block[1],
		   inode->i_block[2],
		   inode->i_block[3],
		   inode->i_block[4],
		   inode->i_block[5],
		   inode->i_block[6],
		   inode->i_block[7],
		   inode->i_block[8],
		   inode->i_block[9],
		   inode->i_block[10],
		   inode->i_block[11],
		   inode->i_block[12],
		   inode->i_block[13],
		   inode->i_block[14],
		   inode->i_generation,
		   inode->i_file_acl,
		   inode->i_dir_acl,
		   inode->i_faddr);
	printf("\n");
}

int get_inode_group(Superblock* super, int inode_no){
	int inodes_per_group = super->s_inodes_per_group; /* variável recebe o número de inode por grupo */
	return inode_no / inodes_per_group; /* realiza a operação necessário para saber o grupo do inode */
}

int get_inodes_per_block(Superblock* super){
	return super->s_log_block_size / super->s_inode_size; /* realiza operação necessário para calcular o número de inodes por bloco*/
}

int get_amount_groups_in_block(Superblock* super){
	return 1 + (super->s_blocks_count-1) / super->s_blocks_per_group; /* realiza operação necessário para calcular o número de grupos por bloco*/
}

int get_amount_inodes_in_itable(Superblock* super){
	return super->s_inodes_per_group / get_inodes_per_block(super); /* calcula o número de inodes da tabela de inodes */
}

int get_offset_of_inode_in_itable(Superblock* super, GroupDescriptor* gdesc, int inode_no){
	int inode_group = get_inode_group(super, inode_no); /* recebe o grupo do inode */
	int inode_table = gdesc[inode_group].bg_inode_table; /* recebe tabela de inode */
	int offset = BLOCK_OFFSET(inode_table)+(inode_no-1)*sizeof(Inode) % super->s_inodes_per_group; /* offset é calculado */
	return offset;
}

uint32_t read_dir(FILE* file, Inode *inode, GroupDescriptor *group, char* nomeArquivo)
{
	void *block;

	if (S_ISDIR(inode->i_mode)) {
		struct ext2_dir_entry_2 *entry;
		unsigned int size = 0;

		if ((block = malloc(BLOCK_SIZE)) == NULL) { /* aloca memória para o bloco de dados */
			fprintf(stderr, "Memory error\n");
			fclose(file);
			exit(1);
		}

		fseek(file, BLOCK_OFFSET(inode->i_block[0]), SEEK_SET);
		fread(block, BLOCK_SIZE, 1, file);                /* lê bloco do disco */

		entry = (struct ext2_dir_entry_2 *) block;  /* primeira entrada no diretório */
      
		int found_file = 0;
		
		while((size < inode->i_size) && entry->inode) {
			char file_name[EXT2_NAME_LEN+1];
			memcpy(file_name, entry->name, entry->name_len);
			file_name[entry->name_len] = 0;     /* anexa caractere nulo ao nome do arquivo */
			if(strcmp(nomeArquivo, file_name) == 0){
				return entry->inode;
				found_file = 1;
			}else{
				found_file = 0;
			}

			/* atualiza estrutura e variável */
			entry = (void*) entry + entry->rec_len; 
			size += entry->rec_len;
		}
		if(!found_file) printf(RED("file not found")); /* exibe caso arquivo não foi encontrado */
		printf("\n");
		free(block);
	}
} 

void read_all_dirs_and_push_into_stack(FILE* file, Inode *inode, GroupDescriptor *group, StackDirectory* stack, char* name){
	void *block;
	struct ext2_dir_entry_2 *entry;
	unsigned int size = 0;

	ListDirEntry* listDirEntry = createListDirEntry(); /* cria lista de entradas */

	if ((block = malloc(BLOCK_SIZE)) == NULL) { /* alaoca memória para o bloco de dados */
		fprintf(stderr, "Memory error\n");
		fclose(file);
		exit(1);
	}

	fseek(file, BLOCK_OFFSET(inode->i_block[0]), SEEK_SET); /* posiciona ponteiro */
	fread(block, BLOCK_SIZE, 1, file);                /* lê bloco do disco */

	entry = (DirEntry*) block;  /* primeira entrada do diretório */
	
	while((size < inode->i_size) && entry->inode) { /* enquanto não ultrapssar tamanho e houver entradas */
		struct NodeDirEntry* nodeListDirEntry;
		nodeListDirEntry = (struct NodeDirEntry*)malloc(sizeof(struct NodeDirEntry));

		char file_name[EXT2_NAME_LEN+1];
		memcpy(file_name, entry->name, entry->name_len);
		file_name[entry->name_len] = 0;     /* anexa caractere nulo no nome do arquivo */
		
		nodeListDirEntry->entry = entry;
		nodeListDirEntry->next = NULL;
		insertDirEntry(listDirEntry, nodeListDirEntry, NULL);

		printf("%10u %s\n", entry->inode, file_name);
		entry = (void*) entry + entry->rec_len;
		size += entry->rec_len;
	}

	NodeStackDirectory* node = (NodeStackDirectory*)malloc(sizeof(NodeStackDirectory));
	node->listDirEntry = listDirEntry;
	push(stack, node, name);
	// free(block);
}

char* convertNumToUnixTime(uint32_t time){
	time_t t = time; /* recebe tempo */
	struct tm ts;
	char* buf = (char*) calloc(80, sizeof(char));
	ts = *localtime(&t); /* recebe estrutura de TIMER */
	int year = 2022;
	sprintf(buf, "%d/%d/%d %d:%d", ts.tm_mday, ts.tm_mon, year, ts.tm_hour, ts.tm_min); /* exibe informações de tempo */
	return buf;
	free(buf);
}