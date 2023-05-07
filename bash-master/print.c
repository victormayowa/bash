#include "main.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

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

/**
 * _atoi - Convert a string to an integer.
 * @s: The pointer to convert
 * Return: A integer
 */

int _atoi(char *s)

{
	int c = 0;
	unsigned int ni = 0;
	int min = 1;
	int isi = 0;

	while (s[c])
	{
	if (s[c] == 45)
	{
	min *= -1;
	}
	while (s[c] >= 48 && s[c] <= 57)
	{
	isi = 1;
	ni = (ni * 10) + (s[c] - '0');
	c++;
	}
	if (isi == 1)
	{
	break;
	}
	c++;
	}
	ni *= min;
	return (ni);
}
