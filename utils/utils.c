#include "utils.h"

void print_superblock(struct ext2_super_block super){
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
	       "mount time...................: %" PRIu32 "\n"
	       "white time...................: %" PRIu32 "\n"
	       "mount count..................: %" PRIu16 "\n"
	       "max mount count..............: %" PRIu16 "\n"
	       "magic signature..............: %" PRIu16 "\n"
	       "file system state............: %" PRIu16 "\n"
	       "errors.......................: %" PRIu16 "\n"
	       "minor revision level.........: %" PRIu16 "\n"
	       "time of last check...........: %" PRIu32 "\n"
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
	       super.s_inodes_count,  
	       super.s_blocks_count,
	       super.s_r_blocks_count,     /* reserved blocks count */
	       super.s_free_blocks_count,
	       super.s_free_inodes_count,
	       super.s_first_data_block,
	       super.s_log_block_size,
		   super.s_log_frag_size,
	       super.s_blocks_per_group,
		   super.s_frags_per_group,
	       super.s_inodes_per_group,
		   super.s_mtime,
		   super.s_wtime,
		   super.s_mnt_count,
		   super.s_max_mnt_count,
		   super.s_magic,
		   super.s_state,
		   super.s_errors,
		   super.s_minor_rev_level,
		   super.s_lastcheck,
		   super.s_checkinterval,
	       super.s_creator_os,
		   super.s_rev_level,
		   super.s_def_resuid,
		   super.s_def_resgid,
	       super.s_first_ino,          /* first non-reserved inode */
	       super.s_inode_size,
		   super.s_block_group_nr,
		   super.s_feature_compat,
		   super.s_feature_incompat,
		   super.s_feature_ro_compat,
		   super.s_uuid[0],
		   super.s_volume_name,
		   super.s_last_mounted,
		   super.s_algorithm_usage_bitmap,
		   super.s_prealloc_blocks,
		   super.s_prealloc_dir_blocks,
		   super.s_journal_uuid[0],
		   super.s_journal_inum,
		   super.s_journal_dev,
		   super.s_last_orphan,
		   super.s_hash_seed[0],
		   super.s_def_hash_version,
		   super.s_default_mount_opts,
		   super.s_first_meta_bg);
}