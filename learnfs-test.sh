#!/bin/bash

#
# Author: Ritesh Harjani <ritesh.harjani@gmail.com
# Small test script for learnfs.
#

FS=learnfs
FS_PATH=/data/mnt
LEARNFS_MOD=/data/learnfs.ko
TESTFILE=$FS_PATH/fsimage

learnfs_test_reset() {
	echo "unmount learnfs"
	umount $FS_PATH
	echo "rmmod learnfs\n"
	rmmod $FS
}

learnfs_test_init() {
	echo "mkdir /data/mnt"
	mkdir $FS_PATH

	if [ -e $LEARNFS_MOD ]
	then
		echo "insmod learnfs"
		insmod $LEARNFS_MOD
	else
		echo "no learnfs module found. Exiting..."
	fi

	echo "mounting learnfs\n"
	mount -t $FS nodev $FS_PATH
	return $?
}

learnfs_write() {
	COUNT=10
	BS=1m
	echo "[Write Test]: Executing write in bs=$BS at $TESTFILE"
	dd if=/dev/zero of=$TESTFILE bs=$BS count=$COUNT
	echo "Done.\n"
}

learnfs_read() {
	COUNT=10
	BS=4k
	echo "[Read Test]: Executing read in bs=$BS at $TESTFILE"
	dd if=$TESTFILE of=/dev/zero bs=$BS count=$COUNT
	echo -e "Done.\n"
}


learnfs_test_reset
learnfs_test_init


learnfs_write
learnfs_read
