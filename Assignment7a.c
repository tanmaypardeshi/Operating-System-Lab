#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <sys/wait.h>
#define BUFFER_SIZE 50

int main(void)
{

	char filename[BUFFER_SIZE], buffer[BUFFER_SIZE];
	int pipe1[2],pipe2[2],pid,i;
	int no_spaces, no_tabs, no_lines, no_words;
	
	FILE * file; 

	if(pipe(pipe2) == -1)
		return 1;
	
	if(pipe(pipe1) == -1)
		return 1;
		
	if(pipe(pipe1) == 0 && pipe(pipe2) == 0)
		pid = fork();
		
	if (pid != 0)  // parent process
	{ 
		

		printf("Enter filename to read:- ");
		scanf("%s", filename);

		file = fopen(filename, "r");

		if(file == NULL)
		{
			printf("File %s not found", filename);
			return 0;
		}

		close(pipe1[0]);
		write(pipe1[1], filename, strlen(filename)+1);
		close(pipe1[1]);

		sleep(2);

		close(pipe2[1]);
		read(pipe2[0], buffer, BUFFER_SIZE);
		close(pipe2[0]);
		i = 0;
		while(1)
		{
			if(buffer[i] == '\0')
			{
				break;
			}
			if(buffer[i] == ' ')
			{
				no_spaces++;
			}
			if(buffer[i] == '\t')
			{
				no_tabs++;
			}
			if(buffer[i] == '\n')
			{
				no_lines++;
			}
			if(buffer[i] == ' ' || buffer[i] == '\n')
			{
				no_words++;
			}
			i++;
		}	
		printf("\nParent process has read the contents from pipe 2:- %s\n", buffer);
		printf("\nNo of spaces are %d", no_spaces);	
		printf("\nNo of tabs are %d", no_tabs);
		printf("\nNo of lines are %d", no_lines);
		printf("\nNo of words are %d\n", no_words);
		wait(NULL);
	}	
	else // child process
	{ 	
		close(pipe1[1]);
		read(pipe1[0], filename, BUFFER_SIZE);
		close(pipe1[0]);

		file = fopen(filename, "r");

		printf("\nChild is reading filename %s", filename);		
		while(1)
		{
			buffer[i] = fgetc(file);
			if(buffer[i] == EOF)
				break;
			i++;
		}

		buffer[i] = '\0';

		fclose(file);

		close(pipe2[0]);
		write(pipe2[1], buffer, strlen(buffer) + 1);
		close(pipe2[1]);

		printf("\nChild has written content on pipe 2\n");
	}

	return 0;
}
