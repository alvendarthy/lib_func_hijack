#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include<stdarg.h>

void *malloc(size_t size) {
    printf("called..my malloc\n");

    void *(*glibc_malloc)(size_t size);
    // Find original malloc function
    glibc_malloc = dlsym(RTLD_NEXT, "malloc");

    if ( dlerror() != NULL)
    {
        puts("malloc symbol not found..\n");
        exit(1);
    }

    printf("This should call actual malloc now..\n");
    return (*glibc_malloc)(size);
}


void free(void * addr){
    if( NULL == addr){
        return;
    }
    printf("free memory at %p\n", addr);

    void (*glibc_free)(void *);

    glibc_free = dlsym(RTLD_NEXT, "free");

    if ( dlerror() != NULL)
    {
        puts("free symbol not found..");
        exit(1);
    }

    return glibc_free(addr);
}


int open(const char* filename,  int flags, ...){

    printf("open file: %s; as mode %d \n", filename, flags);

    va_list args;
    va_start(args, flags);


    int (*glibc_open)(const char * filename,  int flags, ...);

    glibc_open = dlsym(RTLD_NEXT, "open");

    return glibc_open(filename, flags, args);
}

ssize_t write (int fd, const void * buf, size_t count){

    char buffer[1024] = {0};

    snprintf(buffer, 1024, "encrypt:%s", (const char *) buf);


    ssize_t (*glibc_write)(int fd, const void * buf, size_t count);

    glibc_write = dlsym(RTLD_NEXT, "write");

    return glibc_write(fd, buffer, strlen(buffer));
}
