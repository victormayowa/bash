#include "main.h"

/**
  * _strchr - returns first occurence of the char c in string s
  * @s: string where c is searched
  * @c: character that is searched
  * Return: a pointer to the matched character, NULL if not found
  */

char *_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (*s == (char)c)
	{
		return ((char *)s);
	}
	return (NULL);
}

