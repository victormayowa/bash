#include "main.h"

/**
 * main - main function for simple shell
 * @argc: argument count
 * @argv: argument vector
 * Return: Always 0.
 */

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		int input_fd = open(argv[1], O_RDONLY);

		if (input_fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		handle_non_interactive_mode(input_fd);
		close(input_fd);
	}
	else
	{
		handle_interactive_mode();
	}
	return (0);
}
