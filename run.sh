#!/bin/sh

qemu-system-arm -M versatilepb -cpu arm1176 -nographic -kernel kernel.elf
