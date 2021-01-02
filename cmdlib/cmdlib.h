// cmdlib.h

#ifndef __CMDLIB__
#define __CMDLIB__

#include <ctype.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/io.h>
#include <sys/stat.h>

#ifndef __BYTEBOOL__
#define __BYTEBOOL__
typedef enum { false, true } boolean;
typedef unsigned char byte;
#endif

#define PATHSEPERATOR '/'

void Error(char *error, ...);

int SafeOpenRead(char *filename);
void SafeRead(int handle, void *buffer, long count);
void SafeWrite(int handle, void *buffer, long count);
void *SafeMalloc(long size);

long LoadFile(char *filename, void **bufferptr);

extern byte *screen;

#endif
