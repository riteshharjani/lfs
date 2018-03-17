#include <linux/fs.h>

#define LEARNFS_MAGIC	0x4C4541524E //LEARN

struct inode *learnfs_iget(struct super_block *sb, struct inode *dir, umode_t mode);
extern struct inode_operations learnfs_dir_inode_operations;
