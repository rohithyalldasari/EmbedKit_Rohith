# EmbedKit_Rohith

Name: Rohith Yalldasari

## Description
A lightweight and optimized circular ring buffer utility implemented in C.

## Module
### ringbuf.c
Implements an 8-byte circular buffer (FIFO) supporting initialization, write, read, full/empty checks, and count tracking.

## Build Instructions

Compile:
gcc -Wall -std=c99 ringbuf.c -o ringbuf

Run:
./ringbuf

## Features
- Fixed-size 8-byte ring buffer
- FIFO data handling
- Buffer full detection
- Buffer empty detection
- Count tracking
- Efficient wrap-around using bitwise AND optimization
