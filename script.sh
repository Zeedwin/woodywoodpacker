#!/bin/bash

nasm -f elf64 bootloader.s -o bootloader.o
clang main.c bootloader.o
./a.out