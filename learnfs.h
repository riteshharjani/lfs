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

#include <linux/fs.h>

#define LEARNFS_MAGIC	0x4C4541524E //LEARN

struct inode *learnfs_iget(struct super_block *sb, struct inode *dir, umode_t mode);
extern struct inode_operations learnfs_dir_inode_operations;
extern struct inode_operations learnfs_file_inode_operations;
extern struct address_space_operations learnfs_aops;
extern struct file_operations learnfs_file_operations;
