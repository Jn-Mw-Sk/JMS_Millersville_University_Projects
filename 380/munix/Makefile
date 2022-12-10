# File: Makefile
# Author: Chad Hogg
# Compilation instructions for CSCI380 munix lab.

all : driver.out mkdisk.out

driver.out : driver.c munix.c mufs.c muusers.c muerrno.c
	gcc -g -Wall -o $@ $^

mkdisk.out : mkdisk.c mufs.c muusers.c
	gcc -g -Wall -o $@ $^
