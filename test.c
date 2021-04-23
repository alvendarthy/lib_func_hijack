#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){

    // malloc and free are injected
    int * a = malloc(sizeof(int));

    *a = 10;

    printf("%p --> %d\n", a, *a);

    free(a);

    printf("done\n");

    printf("open file.");
    int fd = open("./tmp.txt", O_RDWR|O_CREAT);

    char * data = "hello world!";

    
    // write is injected too, add a prefix of "encrypted:" to any data, see tmp.txt
    write(fd, data, strlen(data));

    // get filename by fd

    char buf[1024] = {0};
    char linkPath[1024] = {0};

    snprintf(linkPath, 1024, "/proc/self/fd/%d", fd);

    printf("link path: %s\n", linkPath);

    int ret = readlink(linkPath, buf, 1024);

    if(ret < 0){
        printf("get fd file name failed.\n");
    } else {
        printf("fd: %d --> filename: %s\n", fd, buf);
    }


    close(fd);

    

    return 0;
}
