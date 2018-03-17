#include <linux/module.h>
#include <linux/fs.h>

#include "learnfs.h"

struct inode *learnfs_iget(struct super_block *sb, struct inode *dir,
				  umode_t mode)
{
	struct inode *inode = new_inode(sb);

	if (!inode)
		goto out;

	inode->i_atime = inode->i_ctime = inode->i_mtime = current_time(inode);
	inode_init_owner(inode, dir, mode);

	switch(mode & S_IFMT) {
	case S_IFREG:
		inode->i_op = &learnfs_file_inode_operations;
		break;
	case S_IFDIR:

		/*
		 * Without below operation
		 * change directory(cd) cannot be performed on mounted
		 * filesystem.
		 * As fill_super also calls this function
		 * to allocate it's inode.
		 */
		inode->i_op = &learnfs_dir_inode_operations;

		/*
		 * Without below operation
		 * lookup cannot be performed on the root inode
		 * and hence on the root dir entry.
		 * Hence ls functionality won't work.
		 * file_operations->iterate_dir/_shared is needed
		 */
		inode->i_fop = &simple_dir_operations;

		/*
		 * dir inodes have two entries "." & ".."
		 */
		inc_nlink(inode);
		break;
	default:
		break;
	}

out:
	return inode;
}

static int learnfs_fill_super(struct super_block *sb, void *data,
			      int flags)
{
	struct inode *inode;

	inode = learnfs_iget(sb, NULL, S_IFDIR | 0755);
	if (!inode)
		return -ENOMEM;

	sb->s_root = d_make_root(inode);
	if (!sb->s_root)
		return -ENOMEM;
	sb->s_magic = LEARNFS_MAGIC;
	return 0;
}

struct dentry *learnfs_mount(struct file_system_type *fs_type, int flags,
			     const char *dev_name, void *data)
{
	struct dentry *dentry;

	dentry = mount_nodev(fs_type, flags, data, learnfs_fill_super);
	if (dentry)
		pr_info("%s: Mounted learnfs 0.1 success on %s\n", __func__, dev_name);
	return dentry;
}

void learnfs_kill_sb(struct super_block *sb)
{
	kill_litter_super(sb);
	pr_info("%s: Unmounted learnfs 0.1\n", __func__);
}

static struct file_system_type learnfs_type = {
	.owner = THIS_MODULE,
	.name = "learnfs",
	.fs_flags = 0,
	.mount = learnfs_mount,
	.kill_sb = learnfs_kill_sb,
};

static int __init learnfs_init(void)
{
	register_filesystem(&learnfs_type);
	pr_info("%s: Register learnfs 0.1\n", __func__);
	return 0;
}

static void __exit learnfs_exit(void)
{
	unregister_filesystem(&learnfs_type);
	pr_info("%s: Unregistered \n", __func__);
}

module_init(learnfs_init);
module_exit(learnfs_exit);
