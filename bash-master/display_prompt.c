#include "main.h"

/**
 * display_prompt - Displays the shell prompt
 * Return: void
 */

void display_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 10);
}
