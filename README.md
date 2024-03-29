## learnfs:	Learn filesystem module :file_folder:
##### Author:		Ritesh Harjani <ritesh.harjani@gmail.com>

[![About me](https://img.shields.io/badge/author-rharjani-brightgreen.svg)](https://github.com/riteshharjani)
[![TODO](https://img.shields.io/badge/development-TODO-lightgrey.svg)](#todo-)

==========================================

### Description:
learnfs is a small & simple Ram based filesystem
module which mainly uses the existing library API's of fs/libfs.c
Main goal of writing learnfs is to understand
**_"How to write a linux filesystem"_**

Since it is not disk based fs, so there will be no disk I/O
involved in this case and the address_space mapping APIs will be
straight forward.

**Since _learnfs_ it is written from scratch, every commit of this
will describe the actual process of writing a filesystem.**
While writing sdcardfs & ramfs code was considered as reference.

### TODO:-
1. Implement address_space mapping operation on it's own instead of using libfs.
2. Implement symlink/hardlinks.
3. Remove all libfs.c code and implement yourself.

### To Cross compile for ARM:-
```
export KDIR=<kernel build/kobj path>
export CC=<cross compiler>
make
```
### To Test:-
```
adb root
adb push learnfs.ko /data
adb push learnfs-test.sh /data
adb shell
sh ./data/learnfs-test.sh
```
### learnfs-test.sh Output:-
```
:/data # sh learnfs-test.sh
unmount learnfs
rmmod learnfs

mkdir /data/mnt
mkdir: '/data/mnt': File exists
insmod learnfs
mounting learnfs
```
### [Write Test]:
```
Executing write in bs=1m at /data/mnt/fsimage
10+0 records in
10+0 records out
10485760 bytes transferred in 0.036 secs (291271111 bytes/sec)
Done.
```
### [Read Test]: 
```
Executing read in bs=4k at /data/mnt/fsimage
10+0 records in
10+0 records out
40960 bytes transferred in 0.001 secs (40960000 bytes/sec)
Done.
```

### Contribution:-
1. In case if anyone would like to contribute to this project - please feel free to submit a pull request.

