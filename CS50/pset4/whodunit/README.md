# Questions

## What's `stdint.h`?

A header file in the C standard library.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

To specify the types of data the programmer wants to carry.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

424d 3810

## What's the difference between `bfSize` and `biSize`?

bfSize is the bitmap file size in bytes and biSize is the structure size in bytes.

## What does it mean if `biHeight` is negative?

It means that the bitmap will be written left to right, top to bottom.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

The biBitCount.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

In line 24, the file may not exist. In line 32, there may not be any memory left for outptr to be created.

## Why is the third argument to `fread` always `1` in our code?

Because that is the number of times we needed to read (One struct at a time). However, that number is arbitrary.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

It changes the offset of the file pointer.

## What is `SEEK_CUR`?

An int signaling for fseek to do its agic from the current position.
