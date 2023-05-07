#include "main.h"

/**
 * my_execl - Replace the current process with a new process
 *            specified by path and arguments
 *
 * @path: Path to the executable file
 * @arg: First argument of the new process
 * @...: Variable number of additional arguments
 *
 * Return: On success, does not return. On error, returns -1.
 */
int my_execl(const char *path, const char *arg, ...)
{
	va_list args;
        char *argv[10];
        int argc = 0;
	
	argv[argc++] = (char *)arg;
	
	va_start(args, arg);
	
	while (argc < 10)
	{
		char *arg = va_arg(args, char *);
		
		if (arg == NULL)
			break;
		
		argv[argc++] = arg;
	}

	va_end(args);

	argv[argc] = NULL;
	
	return (execv(path, argv));
}

