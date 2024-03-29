/*
 * Author:	Ritesh Harjani <ritesh.harjani@gmail.com>
 * 		(2018)
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

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

static int learnfs_create(struct inode *dir, struct dentry *dentry, umode_t mode,
			  bool excl)
{
	return learnfs_mknod(dir, dentry, mode | S_IFREG, 0);
}

struct inode_operations learnfs_dir_inode_operations = {
	.lookup = simple_lookup,
	.create = learnfs_create,
	.unlink = simple_unlink,
	.mkdir = learnfs_mkdir,
	.rmdir = simple_rmdir,
	.mknod = learnfs_mknod,
};

struct inode_operations learnfs_file_inode_operations = {
	.setattr = simple_setattr,
	.getattr = simple_getattr,
};
