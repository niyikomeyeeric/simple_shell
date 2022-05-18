#include "shell.h"

/**
* comd_prompt - interpretes UNIX command line
* @buffer: buffer to use
* @nread: numbers of of characters to return
* Returns: numbers of characters read
*/

ssize_t comd_prompt(char *buffer, size_t nread)
{
	int i = 0;
	size_t size = 1;

	buffer = malloc(sizeof(size));
	if (buffer == NULL)
	{
		return (-1);
	}



	printf("$: ");
	while (buffer)
	{
		nread = getline(&buffer, &size, stdin);
		printf("%s\n", buffer);
		printf("%zd\n", nread);
		printf("$: ");

	}
	free(buffer);
	close(nread);
}
