#include <linux/module.h>
#include <linux/fs.h>

static struct file_system_type learnfs_type = {
	.owner = THIS_MODULE,
	.name = "learnfs",
	.fs_flags = 0,
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
