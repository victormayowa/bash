#include "main.h"

/**
  * extract_line - extract line read in
  * @buffer: temp container
  * @buffer_size: size of buffer
  * @pos: position
  * Return: extract line
  */

char *extract_line(char *buffer, int buffer_size, int *pos)
{
	char *line = NULL;
	int i, j;

	while (*pos < buffer_size)
	{
		for (i = *pos, j = 0; i < buffer_size && j < BUFFER_SIZE; i++, j++)
		{
			if (buffer[i] == '\n')
			{
				line = (char *) malloc((j + 1) * sizeof(char));
				if (line == NULL)
				{
					return (NULL);
				}
				for (i = *pos, j = 0; i < buffer_size && buffer[i] != '\n'; i++, j++)
				{
					line[j] = buffer[i];
				}
				line[j] = '\0';
				*pos = i + 1;
				return (line);
			}
		}
		*pos = 0;
		buffer_size = read_input(buffer, BUFFER_SIZE);
	}
	return (NULL);
}
