#include "main.h"

/**
 * my_strtok - tokenize a string
 * @str: the string to tokenize
 * @delim: the delimiter to use for tokenization
 *
 * Return: a pointer to the next token, or NULL if there are no more tokens
 */

char *my_strtok(char *str, const char *delim)
{
	static char *last_token;  /* save last token found by strtok */
	char *start, *end;

	/* If a new string is provided, reset the last token */
	if (str != NULL)
	{
		last_token = str;
	}
	if (last_token == NULL)
	{
		return (NULL);
	}
	start = last_token;
	end = _strpbrk(start, delim);
	if (end != NULL)
	{
		*end = '\0';
		last_token = end + 1;
	}
	else
	{
		last_token = NULL;
	}
	return (start);
}
