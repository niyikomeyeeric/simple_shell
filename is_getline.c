#include "main.h"
/**
 * _getline - reads entire line from a stream
 * @lineptr: space where the stream is stored
 * @n: number of bytes
 * @stream: where input is collected from
 * Return: numbers of chars read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int c;
	size_t count = 0;

	if (*lineptr == NULL)
	{
		*lineptr = malloc(BUFFSIZE);
		if (*lineptr == NULL)
			return (-1);
		*n = BUFFSIZE;
	}
	while (1)
	{
		c = getc(stream);
		if (c == EOF && count == 0)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(*lineptr);
			exit(0);
		}
		if (c == '\n')
			break;
		(*lineptr)[count] =  c;
		count++;
		if (count >= (*n))
		{
			*n = (*n) * 2;
			*lineptr = (char *)realloc(*lineptr, *n);
			if ((*lineptr) == NULL)
				return (-1);
		}
	}
	if (c != '\n')
		putchar('\n');
	(*lineptr)[count] = '\0';
	return (count);
}
