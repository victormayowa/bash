#include "main.h"

/**
  * handle_exit_command - exit shell
  * @args: argument
  * @argc: argument count
  * Return: void
  */
void handle_exit_command(char **args, int argc)
{
	if (argc == 1)
	{
		exit(EXIT_SUCCESS);
	}
	else if (argc == 2)
	{
		int exit_status = _atoi(args[1]);

		exit(exit_status);
	}
	else
	{
		_puts("Usage: exit [status]\n");
		return;
	}
}
