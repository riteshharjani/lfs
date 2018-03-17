#include <linux/module.h>

static int __init learnfs_init(void)
{
	pr_info("%s: Initialization\n", __func__);
	return 0;
}

static void __exit learnfs_exit(void)
{
	pr_info("%s: Exiting\n", __func__);
}

module_init(learnfs_init);
module_exit(learnfs_exit);
