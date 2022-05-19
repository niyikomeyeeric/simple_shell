#include "main.h"

/**
 * main - Entry point
 * @argc: number of arguements
 * @argv: arguement passed into the function
 * Description: Standard output display of shell.
 * Return: 0 on success.
 */

int main(__attribute__((unused))int argc, char **argv)
{
	char *line = NULL, **args;
	int status = 1;
	char **chk_env = environ;
	size_t n = 0;
	unsigned int count;

	do {
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);
		if (chk_env != environ)
			chk_env = NULL;
		count = _getline(&line, &n, stdin);
		if (count == 1)
			continue;
		args = get_args(line);
		status = builtin_args(args, argv);
		if (status < 0)
			status = execute_cmd(args, argv);
		free(args);
	} while (status);
	if (chk_env == NULL)
		free(environ);
	return (0);
}
