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

