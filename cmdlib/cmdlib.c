// cmdlib.c

#include "cmdlib.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

/*
================
=
= filelength
=
================
*/

int myargc;
char **myargv;

int filelength(int handle) {
    struct stat fileinfo;

    if (fstat(handle, &fileinfo) == -1) {
        fprintf(stderr, "Error fstating");
        exit(1);
    }

    return fileinfo.st_size;
}

/*
=============================================================================

                                                MISC FUNCTIONS

=============================================================================
*/

/*
=================
=
= Error
=
= For abnormal program terminations
=
=================
*/

void Error(char *error, ...) {
    va_list argptr;
    va_start(argptr, error);
    vprintf(error, argptr);
    va_end(argptr);
    printf("\n");
    exit(1);
}

int SafeOpenRead(char *filename) {
    int handle;

    handle = open(filename, O_RDONLY);

    if (handle == -1)
        Error("Error opening %s: %s", filename, strerror(errno));

    return handle;
}

void SafeRead(int handle, void *buffer, long count) {

    while (count) {
        unsigned iocount = count > 0x8000 ? 0x8000 : count;
        if (read(handle, buffer, iocount) != iocount)
            Error("File read failure");
        buffer = (void *)((byte *)buffer + iocount);
        count -= iocount;
    }
}

void *SafeMalloc(long size) {
    void *ptr;

    ptr = malloc(size);

    if (!ptr)
        Error("Malloc failure for %lu bytes", size);

    return ptr;
}

long LoadFile(char *filename, void **bufferptr) {
    int handle;
    long length;
    void *buffer;

    handle = SafeOpenRead(filename);
    length = filelength(handle);
    buffer = SafeMalloc(length);
    SafeRead(handle, buffer, length);
    close(handle);

    *bufferptr = buffer;
    return length;
}

// Basic graphics

byte *screen;

#define PEL_WRITE_ADR 0x3c8
#define PEL_READ_ADR 0x3c7
#define PEL_DATA 0x3c9
#define PEL_MASK 0x3c6
