#include "main.h"

/**
 * _puts - Prints every other character of a string
 * @s: The string to be treated
 * Return: void
 */

int _puts(const char *s)
{
	int i = 0;

	if (s == NULL)
	{ /* null pointer check */
		return (EOF);
	}
	while (s[i] != '\0')
	{
		/* iterate until null terminator is reached */
		if (_putchar(s[i]) == EOF)
		{
			/* output each character using putchar */
			return (EOF);
		}
		i++;
	}
	if (_putchar('\n') == EOF)
	{
		/* output newline character at the end */
		return (EOF);
	}
	return (0);
}

