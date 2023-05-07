#include "main.h"

/**
 * handle_non_interactive - handle shell commands from stdin
 * @input_fd: file descriptor for input (STDIN_FILENO)
 */
void handle_non_interactive(void)
{
	char *cmd = NULL;
	size_t len = 0;

	/* Read commands from input_fd */
	while (getline(&cmd, &len, stdin) != -1)
	{
		cmd[_strspn(cmd, "\n")] = '\0';
		command_args(cmd);
	}
	free(cmd);
}

