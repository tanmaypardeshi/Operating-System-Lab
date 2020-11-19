#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#define MAX 80
#define FIFO "FIFO"

int main() 
{ 
    int fd, i;
    char str[MAX], ch; 
  
    mkfifo(FIFO, 0666);

    i = 0;
    while(ch=fgetc(stdin) != 'Q') 
    {
        str[i++] = ch;
    }
    str[i] = '\0';

    fd = open(FIFO, O_WRONLY);

    write(fd, str, strlen(str) + 1);

    close(fd);

    return 0; 
} 