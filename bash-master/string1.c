#include "main.h"

/**
  * _strdup - duplicates the inside another string variable address
  * @s: pointer to the address of the variable where string is copied into
  * Return: pointer
  */

char *_strdup(const char *s)
{
	size_t len = _strlen(s) + 1;
	char *p = malloc(len);

	if (p)
		_strcpy(p, s);
	return (p);
}

/**
 * _strlen - Returns the length of a string
 * @str: The string to get the length of
 *
 * Return: The length of the string
 */

size_t _strlen(const char *str)
{
	size_t len = 0;

	while (str[len] != '\0')
		len++;
	return (len);
}

/**
  * _strpbrk - returns first occurence of any character from accept in s
  * @s: the string to  break
  * @accept: the char to accept
  * Return: char p
  */

char *_strpbrk(const char *s, const char *accept)
{
	const char *p;
	const char *q;

	for (p = s; *p != '\0'; p++)
	{
		for (q = accept; *q != '\0'; q++)
		{
			if (*p == *q)
			{
				return ((char *) p);
			}
		}
	}
	return (NULL);
}

/**
 * _strspn - replicate strcspn function
 * @s: Input
 * @reject: Input
 * Return: Always 0 (Success)
 */

unsigned int _strspn(const char *s, const char *reject)
{
	const char *p, *q;

	for (p = s; *p; p++)
	{
		for (q = reject; *q; q++)
		{
			if (*p == *q)
			{
				return (p - s);
			}
		}
	}
	return (p - s);
}
