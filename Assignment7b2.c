#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#define MAX 100
#define FIFO "FIFO"

int main() 
{ 
    int fd1, fd2, cc = 0, lc = 0, wc = 0, i = 0;
    char str[MAX], *filename1="sample.txt", *filename2="count.txt"; 

    FILE *file;

    mkfifo(filename1, 0666);
    mkfifo(filename2, 0666);

    fd1 = open(filename1, O_RDONLY);
    read(fd1, str, MAX);

    printf("\nReceived the file contents:- %s\n", str);
    
    while(str[i] != '\0')
    {
        if(str[i] == '\n')
        {
            lc++;
        }
        if(str[i] == ' ' || str[i] == '\n')
        {
            wc++;
        }
        cc++;
        i++;
    }
    fd2 = open(filename2, O_WRONLY);

    file = fopen(filename2, "w");
    fprintf(file, "Character Count: %d\nWord Count: %d\nLine Count: %d\n", cc, wc, lc);
    fclose(file);

    write(fd2, str, strlen(str) + 1);
    
    close(fd2);
    close(fd1);
    return 0; 
} 
