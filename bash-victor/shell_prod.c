#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

int is_interactive();
void run_interactive_shell();
void run_non_interactive_shell();
void display_prompt();
void read_input(char *input);
char **split_input_by_semicolon(char *input);
void execute_command(char *command);
int is_comment(char *command);
char *remove_comments(char *command);
int is_logical_operator_present(char *command);
void handle_logical_operator(char *command);
void execute_command_with_logical_or(char *command);
void execute_command_with_logical_and(char *command);
char **split_command_by_logical_operator(char *command, char *operator);
char **parse_command_for_filenames(char *command);
char **parse_command_for_arguments(char *command);
void execute_external_command(char **arguments, char **filenames);

int main()
{
    if (is_interactive())
    {
        run_interactive_shell();
    }
    else
    {
        run_non_interactive_shell();
    }

    return 0;
}

int is_interactive()
{
    return isatty(STDIN_FILENO);
}

void run_interactive_shell()
{
    char input[MAX_INPUT_LENGTH];

    while (1)
    {
        display_prompt();
        read_input(input);

        if (input[0] == '\0')
        {
            continue;
        }

        char **commands = split_input_by_semicolon(input);

        for (int i = 0; commands[i] != NULL; i++)
        {
            execute_command(commands[i]);
        }

        free(commands);
    }
}

void run_non_interactive_shell()
{
    char input[MAX_INPUT_LENGTH];

    read_input(input);

    char **commands = split_input_by_semicolon(input);

    for (int i = 0; commands[i] != NULL; i++)
    {
        execute_command(commands[i]);
    }

    free(commands);
}

void display_prompt()
{
    printf("shell_prompt> ");
}

void read_input(char *input)
{
    fgets(input, MAX_INPUT_LENGTH, stdin);

    // Remove newline character from input
    input[strcspn(input, "\n")] = '\0';
}

char **split_input_by_semicolon(char *input)
{
    char **commands = malloc(sizeof(char *) * MAX_INPUT_LENGTH);
    char *token;
    int i = 0;

    token = strtok(input, ";");

    while (token != NULL)
    {
        commands[i] = strdup(token);
        i++;
        token = strtok(NULL, ";");
    }

    commands[i] = NULL;

    return commands;
}

void execute_command(char *command)
{
    if (is_comment(command))
    {
        return;
    }

    command = remove_comments(command);

    if (is_logical_operator_present(command))
    {
        handle_logical_operator(command);
    }
    else
    {
        execute_external_command(parse_command_for_arguments(command), parse_command_for_filenames(command));
    }
}

int is_comment(char *command)
{
    return (command[0] == '#');
}

char *remove_comments(char *command)
{
    char *comment_pos = strchr(command, '#');

    if (comment_pos != NULL)
    {
        *comment_pos = '\0';
    }

    return command;
}

int is_logical_operator_present(char *command)
{
    return (strstr(command, "||") != NULL || strstr(command, "&&") != NULL);
}

void handle_logical_operator(char *command)
{
    if (strncmp(command, "||", 2) == 0)
    {
       
