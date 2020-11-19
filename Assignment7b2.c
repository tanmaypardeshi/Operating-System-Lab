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
    int wc = 0, lc = 0, cc = 0, fd, i;

    char str[MAX];

    mkfifo(FIFO, 0666);

    fd = open(FIFO, O_RDONLY);

    read(fd, str, sizeof(str));

    for(i = 0; str[i] != '\0'; i++) 
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
    }

    printf("\nNo of words are:- %d", wc);
    printf("\nNo of lines are:- %d", lc);
    printf("\nNo of character are:- %d\n", cc);

    return 0; 
} 