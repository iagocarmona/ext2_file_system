#include "attr.h"

void attrCommand(FILE* file, struct ext2_inode inode, struct ext2_group_desc *group, struct ext2_super_block* super, char* file_name){
    uint32_t inode_no = read_dir(file, &inode, group, file_name);

    if(!inode_no) return;
    
	read_inode(file, inode_no, group, &inode, super);

    int mode = inode.i_mode; /* formato e atributos do inode */   
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

    /* verifica o tipo do arquivo */
    if(mode & 0x4000) file_type = 'd'; 
    if(mode & 0x8000) file_type = 'f';

    // ================ user fields ============== 
    if(mode & 0x0100){
        user_read = 'r';
    } else {
        user_read = '-';
    }

    if(mode & 0x0080){
        user_write = 'w';
    }else {
        user_write = '-';
    }

    if(mode & 0x0040){
        user_execute = 'x';
    }else {
        user_execute = '-';
    }

    // ================ groud fields ============== 
    if(mode & 0x0100){
        group_read = 'r';
    } else {
        group_read = '-';
    }

    if(mode & 0x0080){
        group_write = 'w';
    }else {
        group_write = '-';
    }

    if(mode & 0x0040){
        group_execute = 'x';
    }else {
        group_execute = '-';
    }

    // ================ others fields ============== 
    if(mode & 0x0100){
        others_read = 'r';
    } else {
        others_read = '-';
    }

    if(mode & 0x0080){
        others_write = 'w';
    }else {
        others_write = '-';
    }

    if(mode & 0x0040){
        others_execute = 'x';
    }else {
        others_execute = '-';
    }

    float size;
    char* size_text;

    /* tamanho do arquivo */
    if(inode.i_size < 1024){
        size = inode.i_size;
        size_text = "Bytes";
    }else {
        size = inode.i_size / 1024;
        size_text = "KiB";
    }
    
    /* hora da montagem */
    char* mtime = convertNumToUnixTime(inode.i_mtime);

    printf("permissões\tuid\tgid\ttamanho\t\tmodificado em\n"); /* exibe informações do arquivo */
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