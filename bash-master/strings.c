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

/**
  * _strcpy - copies the string pointed to by src, including termination
  * @dest: buffer destination
  * @src: address of string to copy
  * Return: pointer to the destination string dest
  */

char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
  * _strncpy - does strcpy except that at most n byte of src are copied
  * @dest: buffer destination
  * @src: address of string to copy
  * @n: number of byte of src to copy
  * Return: pointer to the destination string dest
  */

char *_strncpy(char *dest, const char *src, size_t n)
{
	char *start = dest;

	while (n > 0 && *src != '\0')
	{
		*dest = *src;
		++dest;
		++src;
		--n;
	}
	while (n > 0)
	{
		*dest = '\0';
		++dest;
		--n;
	}
	return (start);
}

