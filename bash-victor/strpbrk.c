#include "main.h"

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

