#include "cmdlib.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

// globals for command line args
//extern int NXArgc;
//extern char **NXArgv;

extern int myargc;
extern char **myargv;
//#define myargc  NXArgc
//#define myargv  NXArgv

int filelength(int handle) {
    struct stat fileinfo;

    if (fstat(handle, &fileinfo) == -1) {
        fprintf(stderr, "Error fstating");
        exit(1);
    }

    return fileinfo.st_size;
}

int tell (int handle)
{
	return lseek (handle, 0, L_INCR);
}

// For abnormal program terminations

void Error(char *error, ...) {
    va_list argptr;
    va_start(argptr, error);
    vprintf(error, argptr);
    va_end(argptr);
    printf("\n");
    exit(1);
}

// Checks for the given parameter in the program's command line arguments
// Returns the argument number (1 to argc-1) or 0 if not present

int CheckParm(char *check, int argc, char *argv[])
{
	int             i;
	char    *parm;

	for (i = 1;i< argc;i++)
	{
		parm = argv[i];

		if ( !isalpha(*parm) )  // skip - / \ etc.. in front of parm
			if (!*++parm)
				continue;               // parm was only one char

		if ( !strcasecmp(check,parm) )
			return i;
	}

	return 0;
}

int SafeOpenWrite (char *filename)
{
	int     handle;

	handle = open(filename, 0666);

	if (handle == -1)
		Error ("Error opening %s: %s",filename,strerror(errno));

	return handle;
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

void SafeWrite(int handle, void *buffer, long count)
{
	unsigned        iocount;

	while (count)
	{
		iocount = count > 0x8000 ? 0x8000 : count;
		if (write (handle,buffer,iocount) != iocount)
			Error ("File write failure");
		buffer = (void *)( (byte *)buffer + iocount );
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

void SaveFile(char *filename, void *buffer, long count)
{
	int             handle;

	handle = SafeOpenWrite (filename);
	SafeWrite (handle, buffer, count);
	close (handle);
}

void DefaultExtension(char *path, char *extension)
{
	char    *src;
//
// if path doesn't have a .EXT, append extension
// (extension should include the .)
//
	src = path + strlen(path) - 1;

	while (*src != PATHSEPERATOR && src != path)
	{
		if (*src == '.')
			return;                 // it has an extension
		src--;
	}

	strcat (path, extension);
}

void StripFilename(char *path)
{
	int length;

	length = strlen(path)-1;
	while (length > 0 && path[length] != PATHSEPERATOR)
		length--;
	path[length] = 0;
}

void StripExtension(char *path)
{
	int length;

	length = strlen(path)-1;
	while (length > 0 && path[length] != '.')
		length--;
	if (length)
		path[length] = 0;
}
