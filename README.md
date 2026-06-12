# EmbedKit_Rohith

Name: Rohith Yalldasari

## Description
A lightweight and optimized circular ring buffer utility implemented in C.

## Module
### ringbuf.c
Implements an 8-byte circular buffer (FIFO) supporting:
- Initialization
- Write operation
- Read operation
- Count tracking
- Full/Empty detection
- Wrap-around using bitwise optimization

## Build Instructions

Compile:
gcc -Wall -std=c99 ringbuf.c -o ringbuf

Run:
./ringbuf
