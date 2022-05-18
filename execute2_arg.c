#include "main.h"

/**
 * exec_cmd - Execute a args that are not directories
 * @args: arguement
 * @argv: arguement passed into the function
 * Return: returns 1 if successfully executed
 */
int exec_cmd(char **args, char **argv)
{
	char *pathenv, *token,  *path;
	int  check_run = 0, count = 0;
	struct stat st;

	pathenv = _getenv("PATH");
	pathenv = _strdup(pathenv);
	token = _strtok(pathenv, ":");
	while (token != NULL)
	{
		path = _strcat(token, args[0]);
		if (stat(path, &st) == 0)
		{
			args[0] = path;
			if (access(args[0], X_OK) == 0)
			{
				execute(args, argv);
				free(path);
			}
			else
			{
				count = _strlen(argv[0]);
				write(STDERR_FILENO, argv[0], count);
				write(STDERR_FILENO, ": permission denied", 19);				free(path);
			}
			check_run++;
			break;
		}
		free(path);
		token = _strtok(NULL, ":");
	}
	if (check_run == 0)
		check_run = check_cwd(check_run, args, argv);
	if (check_run < 1)
	{
		count = _strlen(argv[0]);
		if (isatty(STDIN_FILENO))
		{
			write(STDERR_FILENO, argv[0], count);
			write(STDERR_FILENO, ": No such file or directory\n", 28);
		}
		else
		{
			write(STDERR_FILENO, argv[0], count);
			write(STDERR_FILENO, " 1: ", 4);
			count = _strlen(args[0]);
			write(STDERR_FILENO, args[0], count);
			write(STDERR_FILENO, ": not found\n", 12);
		}
	}
	free(pathenv);
	return (1);
}
