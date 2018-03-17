/*
 * Author:	Ritesh Harjani <ritesh.harjani@gmail.com>
 * 		(2018)
 * Simple test module for testing read/write address_space operations.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	char *buffer;
	int ret;
	int fd;

	buffer = malloc(2* 4096);
	memset(buffer, 0x4C, 2* 4096);

	/*
	 * assuming learnfs is mounted at /data/mnt
	 */
	fd = open("/data/mnt/hello.txt", O_RDWR);
	if (fd < 0)
		return fd;
	ret = write(fd, buffer, 2 * 4096);
	if (ret != 2 * 4096) {
		printf("%s: Error written bytes %d\n", __func__, ret);
		return -1;
	}
	fsync(fd);
	close (fd);

	fd = open("/data/mnt/hello.txt", O_RDONLY);
	if (fd < 0)
		return fd;
	ret = read(fd, buffer, 2 * 4096);
	if (ret != 2 * 4096) {
		printf("%s: Error read bytes %d\n", __func__, ret);
		return -1;
	}
	close (fd);
	return 0;
}
