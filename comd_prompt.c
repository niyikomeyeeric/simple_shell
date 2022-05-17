#include "shell.h"

void comd_prompt(char *buffer, size_t nread)
{
	int i = 0;
	size_t size = 1;
	buffer = malloc(sizeof(size));



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
