#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#define MAX 600

int main()
{
    int fd1, fd2, ch;
    char str[MAX], *filename1 = "sample.txt", *filename2 = "count.txt";
    
    mkfifo(filename1, 0666);
    mkfifo(filename2, 0666);
    
    fd1 = open(filename1, O_WRONLY);
    
    printf("\nPlease enter some text:- ");
    scanf("%[^\\;]s", str);

    write(fd1, str, strlen(str) + 1);

    fd2 = open(filename2, O_RDONLY);
    read(fd2, str, MAX);
    printf("%s\n",str);
    
    close(fd2);
    close(fd1);
    return 0;
}