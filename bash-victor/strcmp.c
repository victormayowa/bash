#include "main.h"

/**
 * _strcmp - compare two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: an integer greater than, equal to, or less than 0, depending
 * on the lexicographical order of the two strings
 */

int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strncmp - compare two strings up to a given number of characters
 * @s1: first string
 * @s2: second string
 * @n: maximum number of characters to compare
 *
 * Return: an integer less than, equal to, or greater than zero if s1 is
 * found, respectively, to be less than, to match, or be greater than s2.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 && *s1 == *s2)
	{
		++s1;
		++s2;
		--n;
	}
	return (n == 0 ? 0 : *s1 - *s2);
}

