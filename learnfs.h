#include <linux/fs.h>

#define LEARNFS_MAGIC	0x4C4541524E //LEARN

struct inode *learnfs_iget(struct super_block *sb, struct inode *dir, umode_t mode);
extern struct inode_operations learnfs_dir_inode_operations;
extern struct inode_operations learnfs_file_inode_operations;
extern struct address_space_operations learnfs_aops;
extern struct file_operations learnfs_file_operations;
