#include "main.h"

/**
  * command_args - handle command line arguments
  * @cmd_line: pointer to the argument passed
  * Return: void
  */
void command_args(char *cmd_line)
{
	char *arg, **env;
	char *args[MAX_ARG];
	int argc = 0, status;
	pid_t pid;

	arg = my_strtok(cmd_line, " ");
	while (arg != NULL && argc < MAX_ARG)
	{
		args[argc] = arg;
		argc++;
		arg = my_strtok(NULL, " ");
	}
	args[argc] = NULL;
	if (_strcmp(args[0], "exit") == 0)
	{
		handle_exit_command(args, argc);
	}
	
	if (_strcmp(args[0], "env") == 0)
	{
		for (env = environ; *env != NULL; env++)
		{
			_puts(*env);
		}
		return;
	}
	find_command(args);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (my_execvp(args[0], args) == -1)
			perror("command not found");
	}
	else
		waitpid(pid, &status, 0);
}
