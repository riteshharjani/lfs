#include <linux/module.h>
#include <linux/fs.h>

#include "learnfs.h"

static int learnfs_mknod(struct inode *dir, struct dentry *dentry,
			 umode_t mode, dev_t dev)
{
	struct super_block *sb = dir->i_sb;
	struct inode *inode;
	int ret = -ENOSPC;

	inode = learnfs_iget(sb, dir, mode);
	if (inode) {
		d_instantiate(dentry, inode);
		dget(dentry);
		ret = 0;
		dir->i_atime = dir->i_mtime = dir->i_ctime = current_time(dir);
	}
	return ret;
}

static int learnfs_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	int ret;
	ret = learnfs_mknod(dir, dentry, mode | S_IFDIR, 0);
	if (!ret)
		inc_nlink(dir); // since a inode got added to dir entry
	return ret;
}

struct inode_operations learnfs_dir_inode_operations = {
	.lookup = simple_lookup,
	.mkdir = learnfs_mkdir,
	.rmdir = simple_rmdir,
	.mknod = learnfs_mknod,
};

struct inode_operations learnfs_file_inode_operations = {
	.getattr = simple_getattr,
};
