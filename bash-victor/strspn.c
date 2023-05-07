#include "main.h"

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
