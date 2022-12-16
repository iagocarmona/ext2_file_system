#include "attr.h"

void attrCommand(FILE* file, struct ext2_inode inode, struct ext2_group_desc *group, struct ext2_super_block* super, char* file_name){
    uint32_t inode_no = read_dir(file, &inode, group, file_name);

    if(!inode_no) return;
    
	read_inode(file, inode_no, group, &inode, super);

    int mode = inode.i_mode;    
    char file_type,
         user_read,
         user_write,
         user_execute,
         group_read,
         group_write,
         group_execute,
         others_read,
         others_write,
         others_execute;

    if(mode & 0x4000) file_type = 'd';
    if(mode & 0x8000) file_type = 'f';

    // ================ user fields ============== 

    user_read = mode & 0x0100 ? 'r' : '-';
    user_write = mode & 0x0080 ? 'w' : '-';
    user_execute = mode & 0x0040 ? 'x' : '-';

    // ================ groud fields ============== 

    group_read = mode & 0x0100 ? 'r' : '-';
    group_write = mode & 0x0080 ? 'w' : '-';
    group_execute = mode & 0x0040 ? 'x' : '-';

    // ================ others fields ============== 

    others_read = mode & 0x0100 ? 'r' : '-';
    others_write = mode & 0x0080 ? 'w' : '-';
    others_execute = mode & 0x0040 ? 'x' : '-';

    float size;
    char* size_text;

    if(inode.i_size < 1024){
        size = inode.i_size;
        size_text = "Bytes";
    }else {
        size = inode.i_size / 1024;
        size_text = "KiB";
    }

    char* mtime = convertNumToUnixTime(inode.i_mtime);

    printf("permissões\tuid\tgid\ttamanho\t\tmodificado em\n");
    printf("%c%c%c%c%c%c%c%c%c%c\t%u\t%u\t%.2f %s\t%s\n", 
            file_type,
            user_read,
            user_write,
            user_execute,
            group_read,
            group_write,
            group_execute,
            others_read,
            others_write,
            others_execute,
            inode.i_uid,
            inode.i_gid,
            size,
            size_text,
            mtime);
}