#include "main.h"

/**
  * read_input - read input
  * @buffer: temporary container to transfer data
  * @buffer_size: size of buffer
  * Return: return lines of input
  */

int read_input(char *buffer, int buffer_size)
{
	return (read(STDIN_FILENO, buffer, buffer_size));
}
