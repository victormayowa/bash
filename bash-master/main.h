#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <stddef.h>
#include <sys/types.h>
#include <signal.h>
#include <stdarg.h>
#include <fcntl.h>

#define MAX_ARG 1024
#define BUFFER_SIZE 1024

#define PROMPT "#cisfun$ "

char *read_line(void);
int execute_command(char *command);
void print_error(char *message);
int my_execl(const char *path, const char *arg, ...);

/* input hANDLERS */
void handle_input(char *input);
void handle_non_interactive_mode(int input_fd);
void handle_interactive_mode();
void handle_non_interactive(void);

void display_prompt(void);
int my_execvp(const char *file, char *const argv[]);
void command_args(char *cmd_line);
void handle_exit_command(char **args, int argc);
int read_input(char *buffer, int buffer_size);
char *extract_line(char *buffer, int buffer_size, int *pos);
char *my_getline(void);
int _puts(const char *s);

/* functions that handles strings */
int _putchar(char c);
unsigned int _strspn(const char *s, const char *reject);
char *_strchr(const char *s, int c);
size_t _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strncpy(char *dest, const char *src, size_t n);
char *_strdup(const char *s);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strpbrk(const char *s, const char *accept);
int _atoi(char *s);

/* other functions */
char *my_strtok(char *str, const char *delim);
char *my_getenv(const char *name);
void find_command(char **args);
void env(void);
extern char **environ;

#endif
