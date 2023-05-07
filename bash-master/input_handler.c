#include "main.h"

/**
  * handle_input - handles input
  * @input: input
  * Return: strtok
  */

void handle_input(char *input)
{
	char *args[MAX_ARG];
	int argc = 0;
	char *token = strtok(input, " ");

	while (token != NULL && argc < MAX_ARG)
	{
		args[argc++] = token;
		token = strtok(NULL, " ");
	}
	args[argc] = NULL;
	if (strcmp(args[0], "exit") == 0)
		handle_exit_command(args, argc);
	else if (strcmp(args[0], "env") == 0)
	{
		char **env;

		for (env = environ; *env != NULL; env++)
			_puts(*env);
	}
	else
	{
		find_command(args);
		if (my_execvp(args[0], args) == -1)
		{
			perror("command not found");
			exit(EXIT_FAILURE);
		}
	}
}

/**
  * handle_interactive_mode - intetactive mode
  * Return: void
  **/
void handle_interactive_mode(void)
{
	char *input = NULL;
	size_t len = 0;

	/* Read commands from stdin */
	while (1)
	{
		display_prompt();
		if (getline(&input, &len, stdin) == -1)
		{
			_putchar('\n');
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		handle_input(input);
	}
	free(input);
}

/**
  * handle_non_interactive_mode - non interactive mode
  * @input_fd: input
  * Return: 0
  */

void handle_non_interactive_mode(int input_fd)
{
	char *input = NULL;
	size_t len = 0;

	/* Read comm	ands from input_fd */
	while (getline(&input, &len, fdopen(input_fd, "r")) != -1)
	{
		input[strcspn(input, "\n")] = '\0';
		handle_input(input);
	}
	free(input);
}

