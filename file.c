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

static int learnfs_write_begin(struct file *filp, struct address_space *mapping,
				loff_t pos, unsigned len, unsigned flags,
				struct page **pagep, void **fsdata)
{
//	dump_stack();
	return simple_write_begin(filp, mapping, pos, len, flags, pagep, fsdata);
}

static int learnfs_write_end(struct file *filp, struct address_space *mapping,
				loff_t pos, unsigned len, unsigned copied,
				struct page *page, void *fsdata)
{
//	dump_stack();
	return simple_write_end(filp, mapping, pos, len, copied, page, fsdata);
}

static int learnfs_readpage(struct file *filp, struct page *page)
{
//	dump_stack();
	return simple_readpage(filp, page);
}

struct address_space_operations learnfs_aops = {
	.readpage = learnfs_readpage,
	.write_begin = learnfs_write_begin,
	.write_end = learnfs_write_end,
};


ssize_t learnfs_read_iter(struct kiocb *iocb, struct iov_iter *iter)
{
//	dump_stack();
	return generic_file_read_iter(iocb, iter);
}

ssize_t learnfs_write_iter(struct kiocb *iocb, struct iov_iter *iter)
{
//	dump_stack();
	return generic_file_write_iter(iocb, iter);
}

struct file_operations learnfs_file_operations = {
	.read_iter = learnfs_read_iter,
	.write_iter = learnfs_write_iter,
};
