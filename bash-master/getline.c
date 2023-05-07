#include "main.h"
/**
  * my_getline - gets lines
  * Return: line typed
  */
char *my_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static int pos;
	static int size;

	pos = 0;
	size = 0;
	if (pos >= size)
	{
		size = read_input(buffer, BUFFER_SIZE);
		if (size <= 0)
		{
			return (NULL);
		}
		pos = 0;
	}
	return (extract_line(buffer, size, &pos));
}
