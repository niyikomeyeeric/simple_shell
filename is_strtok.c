#include <stdio.h>
#include <string.h>
#include "main.h"

/**
 * check_str - checks string if its start with a delim
 * @str: string passed
 * @delim: delimiter
 * Return: a pointer to string to evaluate
 */

char *check_str(char *str, const char *delim)
{
	int i, k, j, len, count = 0;

	if (*str == '\0')
		return (NULL);
	for (j = 0; delim[j]; j++)
	{
		if (delim[j] == str[0])
		{
			len = _strlen(str);
			for (i = 0; str[i]; i++)
			{
				for (k = 0; delim[k]; k++)
				{
					if (str[i] == delim[k])
					{
						str[i] = '\0';
						count++;
					}
				}
				if (str[i] != '\0')
				{
					str = str + i;
					break;
				}
			}
			if (count == len)
				return (NULL);
		}
	}
	return (str);
}

/**
 * eval_str - evaluates the string for delimeters
 * @str: string to be evaluated
 * @nxt_ptr: stores pointer to next token
 * @delim: delimeter
 * Return: pointer to current token
 */

char *eval_str(char *str, char **nxt_ptr, const char *delim)
{
	int i, k, j, count = 0;

	for (i = 0; str[i]; i++)
	{
		count = 0;
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
				str[i] = '\0';
			if (str[i + 1] == '\0')
			{
				*nxt_ptr = NULL;
				return (str);
			}
			if (str[i] == '\0')
			{
				for (k = 0; delim[k]; k++)
				{
					if (delim[k] == str[i + 1])
						count++;
				}
				if (count == 0)
				{
					*nxt_ptr = (*nxt_ptr) + i + 1;
					return (str);
				}
			}
		}
	}
	return (str);
}

/**
 * _strtok - extract tokens from string
 * @str: string to be evaluated
 * @delim: delimeter
 * Return: tokens of string every successive call till a null char is met
 */

char *_strtok(char *str, const char *delim)
{
	static char *nxt_ptr;

	if (str != NULL)
	{
		str = check_str(str, delim);
		nxt_ptr = str;
	}
	else
		str = nxt_ptr;
	if (str != NULL)
	{
		str = eval_str(str, &nxt_ptr, delim);
		if (str != nxt_ptr)
			return (str);
	}
	nxt_ptr = NULL;
	return (str);
}
