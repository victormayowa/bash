#include "main.h"

/**
 * main - main function for simple shell
 *
 * Return: Always 0.
 */

int main(void)
{
	char *cmd = NULL;

	while (1)
	{
		display_prompt();
		cmd = my_getline();
		if (cmd == NULL)
		{
			_putchar('\n');
			break;
		}
		command_args(cmd);
		free(cmd);
	}
	return (0);
}
