#include "main.h"

/**
 * execute_cmd - calls functions necessary to succesfully execute a command
 * @args: command
 * @argv: arguement passed into the function
 * Return: 1 if command is sucessfully executed otherwise 0
 */

int execute_cmd(char **args, char **argv)
{
	int dir_check, check;

	dir_check = check_dir(args);
	if (dir_check > 0)
		check = check_execute(args, argv);
	else
		check = exec_cmd(args, argv);
	return (check);
}

/**
 * check_dir - check if the command is an absolute path
 * @args: command
 * Return: 1 if it's a directory else 0
 */

int check_dir(char **args)
{
	if ((*(*args)) == '/')
		return (1);
	return (0);
}

/**
 * execute - executes a command in a child process
 * @args: command
 * @argv: arguement passed into the function
 */

void execute(char **args, char **argv)
{
	pid_t child;
	int status, len_argv = 0, len_args = 0;

	child = fork();
	if (child == 0)
	{
		if (execve(args[0], argv, environ) == -1)
		{
			len_args = _strlen(args[0]);
			len_argv = _strlen(argv[0]);
			write(STDERR_FILENO, argv[0], len_argv);
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, args[0], len_args);
			write(STDERR_FILENO, ": Is a directory\n", 17);
			exit(0);
		}
	}
	else if (child < 0)
	{
		len_args = _strlen(args[0]);
		len_argv = _strlen(argv[0]);
		write(STDERR_FILENO, argv[0], len_argv);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, args[0], len_args);
	}
	else
		wait(&status);
}

/**
 * check_execute - checks if the command exits in the path
 * @args: command
 * @argv: arguement passed into the function
 * Return: 1 on success
 */

int check_execute(char **args, char **argv)
{
	struct stat st;
	int count = 0;

	if (stat(args[0], &st) == 0)
	{
		if (access(args[0], X_OK) == 0)
			execute(args, argv);
		else
		{
			count = _strlen(argv[0]);
			write(STDERR_FILENO, argv[0], count);
			write(STDERR_FILENO, ": permission denied", 19);
		}
	}
	else
	{
		count = _strlen(argv[0]);
		write(STDERR_FILENO, argv[0], count);
		write(STDERR_FILENO, ": No such file or directory\n", 28);
	}
	return (1);
}

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
				write(STDERR_FILENO, ": permission denied", 19);
				free(path);
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
		check_cmd_tty(args, argv);
	free(pathenv);
	return (1);
}
