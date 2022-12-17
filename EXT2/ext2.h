/**
 * @file ext2.h
 * @author Iago Ortega Carmona
 * @author Thiago Gariani Quinto
 * @author Reginaldo Gregorio de Souza Neto
 * 
 * @brief arquivo de cabeçalho no qual estão definidas as estrutras usadas pelo EXT2
 * @version 0.5
 * @date 2022-12-02
 * 
 * 
 */

#pragma once

#include <stdint.h>

#define	EXT2_NDIR_BLOCKS		12
#define	EXT2_IND_BLOCK			EXT2_NDIR_BLOCKS
#define	EXT2_DIND_BLOCK			(EXT2_IND_BLOCK + 1)
#define	EXT2_TIND_BLOCK			(EXT2_DIND_BLOCK + 1)
#define	EXT2_N_BLOCKS			(EXT2_TIND_BLOCK + 1)

#define EXT2_NAME_LEN 255

/**
 * @brief estrutura do Superbloco, contém todas as informações sobre a configuração 
 * do sistema de arquivos.
 * 
 */
typedef struct ext2_super_block {
	uint32_t	s_inodes_count;		/* número de inodes */
	uint32_t	s_blocks_count;		/* número de blocos */
	uint32_t	s_r_blocks_count;	/* número de blocos reservados */
	uint32_t	s_free_blocks_count;	/* número de blocos livres */
	uint32_t	s_free_inodes_count;	/* número de inodes livres */
	uint32_t	s_first_data_block;	/* identificador do primeiro bloco de dados */
	uint32_t	s_log_block_size;	/* tamanho do bloco */
	uint32_t	s_log_frag_size;	/* tamanho do fragmento */
	uint32_t	s_blocks_per_group;	/* blocos por grupo */
	uint32_t	s_frags_per_group;	/* fragmentos por grupo */
	uint32_t	s_inodes_per_group;	/* inodes por grupo */
	uint32_t	s_mtime;		/* última vez que o sistema foi montado */
	uint32_t	s_wtime;		/* último acesso de gravação ao sistema de arquivos */
	uint16_t	s_mnt_count;		/* quantas vezes o sistema foi montado desde desde a última verificação */
	uint16_t	s_max_mnt_count;	/* número máximo de vezes que o sistema de arquivos pode ser montado antes que uma verificação completa seja executada */
	uint16_t	s_magic;		/* identifica o sistema de arquivos como Ext2 */
	uint16_t	s_state;		/* estado do sistema de arquivos */
	uint16_t	s_errors;		/* o que fazer quando um erro é detectado  */
	uint16_t	s_minor_rev_level; 	/* nível de revisão secundário dentro de seu nível de revisão  */
	uint32_t	s_lastcheck;		/* tempo da última verificação do sistema de arquivos */
	uint32_t	s_checkinterval;	/* intervalo de tempo máximo permitido entre as verificações do sistema de arquivos. */
	uint32_t	s_creator_os;		/* ID do sistema operacional que criou sistema de arquivos */
	uint32_t	s_rev_level;		/* nível de revisão */
	uint16_t	s_def_resuid;		/* ID de usuário padrão para blocos reservados */
	uint16_t	s_def_resgid;		/* ID de grupo padrão para blocos reservados */
	uint32_t	s_first_ino; 		/* índice para o primeiro inode utilizável para arquivos padrão */
	uint16_t   s_inode_size; 		/* tamanho da estrutura do inode */
	uint16_t	s_block_group_nr; 	/* número do grupo de blocos que hospeda essa estrutura superbloco. */
	uint32_t	s_feature_compat; 	/* máscara de 32 bits de recursos compatíveis */
	uint32_t	s_feature_incompat; 	/* máscara de 32 bits de recursos incompatíveis */
	uint32_t	s_feature_ro_compat; 	/* máscara de 32 bits de recursos “somente leitura"  */
	uint8_t	s_uuid[16];		/* ID do volume */
	char	s_volume_name[16]; 	/* nome do volume */
	char	s_last_mounted[64]; 	/* diretório onde o sistema de arquivos foi montado pela última vez */
	uint32_t	s_algorithm_usage_bitmap; /* métodos de compactação usados */
	uint8_t	s_prealloc_blocks;	/* número de blocos que a implementação deve tentar pré-alocar ao criar um novo arquivo regular */
	uint8_t	s_prealloc_dir_blocks;	/* número de blocos que a implementação deve tentar pré-alocar ao criar um novo diretório */
	uint16_t	s_padding1;
	uint8_t	s_journal_uuid[16];	/* uuid do superbloco de diário */
	uint32_t	s_journal_inum;		/* número de inode do arquivo de diário */
	uint32_t	s_journal_dev;		/* número de dispositivo do arquivo de diário */
	uint32_t	s_last_orphan;		/* primeiro inode na lista de inodes a serem excluídos */
	uint32_t	s_hash_seed[4];		/* algoritmo de hash para indexação de diretório */
	uint8_t	s_def_hash_version;	/* versão de hash padrão usada para indexação de diretório. */
	uint8_t	s_reserved_char_pad;
	uint16_t	s_reserved_word_pad;
	uint32_t	s_default_mount_opts; /* opções de montagem padrão para este sistema de arquivos */
 	uint32_t	s_first_meta_bg; 	/* ID do grupo de blocos do primeiro metagrupo de blocos */
	uint32_t	s_reserved[190];	/* preenchimento até o final do bloco  */
}Superblock;


/**
 * @brief estrutra do Descritor do Grupo de Blocos, contém informações sobre onde
 * as estruturas de dados importantes para esse grupo de bloco estão localizadas
 * 
 */
typedef struct ext2_group_desc {
	uint32_t	bg_block_bitmap;	/* endereço do bloco do bitmap de uso do bloco */
	uint32_t	bg_inode_bitmap;	/* endereço do bloco do bitmap de uso do inode */
	uint32_t	bg_inode_table;		/* endereço do bloco inicial da tabela de inodes */
	uint16_t	bg_free_blocks_count;	/* úmero total de blocos livres no grupo*/
	uint16_t	bg_free_inodes_count;	/* número total de inodes livres no grupo */
	uint16_t	bg_used_dirs_count;	/* número total de diretórios */
	uint16_t	bg_pad; /* preencher a estrutura em um limite de 32 bits */
	uint32_t	bg_reserved[3]; /* espaço reservado para futuras revisões */
}GroupDescriptor;


/**
 * @brief estrutura do inode, contém ponteiros para os blocos do sistema de arquivos e 
 * e os metadados de um objeto.
 * 
 */
typedef struct ext2_inode {
	uint16_t	i_mode;		/* formato do arquivo descrito e os direitos de acesso */
	uint16_t	i_uid;		/* ID de usuário de 16 bits associado ao arquivo */
	uint32_t	i_size;		/* tamanho do arquivo em bytes */
	uint32_t	i_atime;	/* hora do último acesso */
	uint32_t	i_ctime;	/* tempo de criação */
	uint32_t	i_mtime;	/* última vez que foi modificado */
	uint32_t	i_dtime;	/* tempo de exclusão */
	uint16_t	i_gid;		/* ID do grupo */
	uint16_t	i_links_count;	/* contagem de hard links */
	uint32_t	i_blocks;	/* número total de blocos */
	uint32_t	i_flags;	/* sinalizadores de arquivo */
	union {
		struct {
			uint32_t  l_i_reserved1; /* valor de 32 bits atualmente reservado */
		} linux1;
		struct {
			uint32_t  h_i_translator; /* tradutor */
		} hurd1;
		struct {
			uint32_t  m_i_reserved1; /* valor de 32 bits atualmente reservado */
		} masix1;
	} osd1;				/* estrutura dependente do sistema operacional de 32 bits */

	uint32_t	i_block[EXT2_N_BLOCKS];/* ponteiros para os blocos */
	uint32_t	i_generation;	/* versão de arquivo */
	uint32_t	i_file_acl;	/* arquivo ACL */
	uint32_t	i_dir_acl;	/* diretório ACL */
	uint32_t	i_faddr;	/* endereço de fragmento */
	union {
		struct {
			uint8_t	l_i_frag;	/* número de fragmento */
			uint8_t	l_i_fsize;	/* tamanho de fragmento */
			uint16_t	i_pad1; 
			uint16_t	l_i_uid_high;	/* id de usuário */
			uint16_t	l_i_gid_high;	/* de id de gruppo  */
			uint32_t	l_i_reserved2; /* reservado */
		} linux2;

		struct {
			uint8_t	h_i_frag;	/* número do fragmento */
			uint8_t	h_i_fsize;	/* tamanho do fragmento */
			uint16_t	h_i_mode_high; /* alto 16 bits do modo de 32 bits */
			uint16_t	h_i_uid_high;  /* id de usuário */
			uint16_t	h_i_gid_high; /* id de grupo */
			uint32_t	h_i_author; /* ID de usuário  do autor do arquivo atribuído */
		} hurd2;

		struct {
			uint8_t	m_i_frag;	/* número do fragmento */
			uint8_t	m_i_fsize;	/* tamanho do fragmento */
			uint16_t	m_pad1; 
			uint32_t	m_i_reserved2[2]; /* reservado */
		} masix2;
	} osd2;				/* estrutura dependente do sistema operacional de 64 bits */

}Inode;


/**
 * @brief estrutura da entrada de diretórios na tabela de inodes
 * 
 */
typedef struct ext2_dir_entry_2 {
	uint32_t	inode;			/* número de inode */
	uint16_t	rec_len;		/* tamanho do diretório */
	uint8_t	name_len;		/* tamanho do nome */
	uint8_t	file_type; /* tipo de arquivo */
	char	name[EXT2_NAME_LEN];			/* nome do arquivo */
}DirEntry;