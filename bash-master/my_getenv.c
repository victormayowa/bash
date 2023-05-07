#include "main.h"

/**
 * my_getenv - get the value of an environment variable
 * @name: the name of the environment variable to get
 *
 * Return: the value of the environment variable, or NULL if it does not exist
 */
char *my_getenv(const char *name)
{
	size_t name_len = _strlen(name);
	char **p;

	for (p = environ; *p; ++p)
	{
		if (_strncmp(name, *p, name_len) == 0 && (*p)[name_len] == '=')
		{
			return (&(*p)[name_len + 1]);
		}
	}
	return (NULL);
}
