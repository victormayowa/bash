#include "main.h"

/**
  * find_command - help to find command by searching for its path
  * @args: argument
  * Return: void
  */

void find_command(char **args)
{
	char *path = my_getenv("PATH");
	char cmd[MAX_ARG];
	char *dir = path;
	int dir_len;
	char *next_colon;

	while (*dir)
	{
		next_colon = _strchr(dir, ':');
		if (next_colon)
		{
			dir_len = next_colon - dir;
		}
		else
		{
			dir_len = _strlen(dir);
		}
		_strncpy(cmd, dir, dir_len);
		cmd[dir_len] = '/';
		_strcpy(&cmd[dir_len + 1], args[0]);
		if (access(cmd, X_OK) == 0)
		{
			args[0] = _strdup(cmd);
			return;
		}
		dir += dir_len;
		if (*dir == ':')
		{
			dir++;
		}
	}
}

