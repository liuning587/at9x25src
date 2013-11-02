#!/bin/sh
mkfs.ubifs -r rootfs -m 2048 -e 126976 -c 240 -o ubifs.img
ubinize -o ubi.img -m 2048 -p 128KiB -s 512 -O 2048 ubinize.cfg

