#include <stdio.h>
#include "main.h"

/**
 * _getenv - gets environmental variable
 * @name: name of variable
 * Return: pointer to value in the environment else NULL
 */

char *_getenv(char *name)
{
	char **env = environ;
	unsigned int i, j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] == name[j])
			j++;
		if (env[i][j] == '=')
			return (&(env[i][j + 1]));
		i++;
	}
	return (NULL);
}
