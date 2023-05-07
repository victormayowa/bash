#include "main.h"

/**
  * my_execvp - replicates the function of execvp (man execvp)
  * @file: the file to execute
  * @argv: pointer to array of  string arguments
  * Return: return -1 on error
  */

int my_execvp(const char *file, char *const argv[])
{
	char *const envp[] = {NULL}; /* pass the current environment */

	return (execve(file, argv, envp));
}

