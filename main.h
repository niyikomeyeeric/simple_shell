#ifndef MAIN_H
#define MAIN_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUFFSIZE 1024

/**
 * struct builtin_fun - struct that execute builtin funnction if seen
 * @name: string to be compared with
 * @f: function pointer
 * Description: struct for builtin function
 */
typedef struct builtin_fun
{
	char *name;
	void (*f)(char **args);
} built_in;
extern char **environ;
void sh_loop(void);
char *eval_str(char *str, char **nxt_ptr, const char *delim);
char *check_str(char *str, const char *delim);
char *_strtok(char *str, const char *delim);

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_getenv(char *name);
int _unsetenv(char *name);
char *setenv_cat(char *name, char *value);
int _setenv(char *name, char *value);
char **get_args(char *line);

int _strlen(char *s);
char *_strcat(char *src, char *dest);
char *_strdup(char *str);
int _strcmp(char *strcmp1, char *strcmp2);

int builtin_args(char **args);
void bui_exit(char **args);
void bui_env(char **args);
void bui_unsetenv(__attribute__((unused))char **args);
void bui_setenv(char **args);
int execute_cmd(char **args, char **argv);
int check_execute(char **args, char **argv);
int check_dir(char **args);
void execute(char **args, char **argv);
int exec_cmd(char **args, char **argv);
int check_cwd(int check_run, char **args, char **argv);

#endif
