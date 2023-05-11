// HEADER FILE //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

void run_interactive_shell();
void run_non_interactive_shell();
void display_prompt();
void read_input(char* input);
char** split_input_by_semicolon(const char* input);
int is_comment(const char* command);
char* remove_comments(char* command);
int is_logical_operator_present(const char* command);
void handle_logical_operator(const char* command);
void execute_command(const char* command);
int is_builtin_command(const char* command);
void handle_builtin_command(const char* command);
void handle_exit_command(const char* command);
void handle_cd_command(const char* command);
void handle_env_command(const char* command);
void handle_setenv_command(const char* command);
void handle_unsetenv_command(const char* command);
void handle_alias_command(const char* command);
char** parse_command_for_filenames(const char* command);
char** parse_command_for_arguments(const char* command);
void execute_external_command(char** arguments, char** filenames);


MAIN GROUP

int main() {
    if (is_interactive()) {
        run_interactive_shell();
    } else {
        run_non_interactive_shell();
    }

    return 0;
}

int is_interactive() {
    return isatty(STDIN_FILENO);
}

void run_interactive_shell() {
    char input[MAX_INPUT_SIZE];
    while (1) {
        display_prompt();
        read_input(input);
        if (input[0] == '\0') {
            continue;
        }
        char** commands = split_input_by_semicolon(input);
        for (int i = 0; commands[i] != NULL; i++) {
            execute_command(commands[i]);
        }
        free(commands);
    }
}

void run_non_interactive_shell() {
    char input[MAX_INPUT_SIZE];
    read_input(input);
    char** commands = split_input_by_semicolon(input);
    for (int i = 0; commands[i] != NULL; i++) {
        execute_command(commands[i]);
    }
    free(commands);
}

void display_prompt() {
    printf("shell_prompt> ");
}

void read_input(char* input) {
    getline(&input, &MAX_INPUT_SIZE, stdin);
    input[strcspn(input, "\n")] = '\0';
}

char** split_input_by_semicolon(const char* input) {
    char** commands = malloc((strlen(input) + 1) * sizeof(char*));
    char* token = strtok(input, ";");
    int i = 0;
    while (token != NULL) {
        commands[i] = strdup(token);
        token = strtok(NULL, ";");
        i++;
    }
    commands[i] = NULL;
    return commands;
}

// EXECUTE COMMAND.
void execute_command(const char* command) {
    if (is_comment(command)) {
        return;
    }

    char* processed_command = remove_comments(command);

    if (is_logical_operator_present(processed_command)) {
        handle_logical_operator(processed_command);
    } else {
        execute_single_command(processed_command);
    }

    free(processed_command);
}

int is_comment(const char* command) {
    return (command[0] == '#');
}

char* remove_comments(char* command) {
    char* comment_pos = strchr(command, '#');
    if (comment_pos != NULL) {
        *comment_pos = '\0';
    }
    return command;
}

// LOGICAL OPERATOR

int is_logical_operator_present(const char* command) {
    return strstr(command, "||") != NULL || strstr(command, "&&") != NULL;
}

void handle_logical_operator(const char* command) {
    if (command[0] == '|') {
        execute_command_with_logical_or(command);
    } else if (command[0] == '&') {
        execute_command_with_logical_and(command);
    }
}

void execute_command_with_logical_or(const char* command) {
    char** subcommands = split_command_by_logical_operator(command, "||");
    for (int i = 0; subcommands[i] != NULL; i++) {
        if (execute_single_command(subcommands[i]) == 0) {
            break;
        }
    }
    free(subcommands);
}

void execute_command_with_logical_and(const char* command) {
    char** subcommands = split_command_by_logical_operator(command, "&&");
    for (int i = 0; subcommands[i] != NULL; i++) {
        if (execute_single_command(subcommands[i]) != 0) {
            break;
        }
    }
    free(subcommands);
}

char** split_command_by_logical_operator(const char* command, const char* operator) {
    char** subcommands = malloc(sizeof(char*) * strlen(command));
    int i = 0;
    char* copy = strdup(command);
    char* token = strtok(copy, operator);
    while (token != NULL) {
        subcommands[i++] = strdup(token);
        token = strtok(NULL, operator);
    }
    subcommands[i] = NULL;
    free(copy);
    return subcommands;
}

// SINGLE AND EXTERNAL COMMANDS

void execute_single_command(const char* command) {
    char** filenames = parse_command_for_filenames(command);
    char** arguments = parse_command_for_arguments(command);
    execute_external_command(arguments, filenames);
    free(filenames);
    free(arguments);
}

char** parse_command_for_filenames(const char* command) {
    char** filenames = malloc(sizeof(char*) * strlen(command));
    int i = 0;
    char* copy = strdup(command);
    char* token = strtok(copy, " \t\r\n");
    while (token != NULL) {
        if (token[0] == '>') {
            filenames[i++] = strdup(token + 1);
        }
        token = strtok(NULL, " \t\r\n");
    }
    filenames[i] = NULL;
    free(copy);
    return filenames;
}

char** parse_command_for_arguments(const char* command) {
    char** arguments = malloc(sizeof(char*) * strlen(command));
    int i = 0;
    char* copy = strdup(command);
    char* token = strtok(copy, " \t\r\n");
    while (token != NULL) {
        if (token[0] != '>') {
            arguments[i++] = strdup(token);
        }
        token = strtok(NULL, " \t\r\n");
    }
    arguments[i] = NULL;
    free(copy);
    return arguments;
}

void execute_external_command(char** arguments, char** filenames) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        if (filenames[0] != NULL) {
            // Redirect output to file
            freopen(filenames[0], "w", stdout);
        }
        if (filenames[1] != NULL) {
            // Redirect error to file
            freopen(filenames[1], "w", stderr);
        }
        execvp(arguments[0], arguments);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}

// BUILT IN FUNCTIONS

int is_builtin_command(const char* command) {
    if (strncmp(command, "@exit", 5) == 0) {
        return 1;
    } else if (strncmp(command, "@cd", 3) == 0) {
        return 1;
    } else if (strncmp(command, "@env", 4) == 0) {
        return 1;
    } else if (strncmp(command, "@setenv", 7) == 0) {
        return 1;
    } else if (strncmp(command, "@unsetenv", 9) == 0) {
        return 1;
    } else if (strncmp(command, "@alias", 6) == 0) {
        return 1;
    }
    return 0;
}

void handle_builtin_command(const char* command) {
    if (strncmp(command, "@exit", 5) == 0) {
        handle_exit_command(command);
    } else if (strncmp(command, "@cd", 3) == 0) {
        handle_cd_command(command);
    } else if (strncmp(command, "@env", 4) == 0) {
        handle_env_command(command);
    } else if (strncmp(command, "@setenv", 7) == 0) {
        handle_setenv_command(command);
    } else if (strncmp(command, "@unsetenv", 9) == 0) {
        handle_unsetenv_command(command);
    } else if (strncmp(command, "@alias", 6) == 0) {
        handle_alias_command(command);
    }
}

void handle_exit_command(const char* command) {
    // Extract the exit status from the command
    const char* exit_status_str = command + 5;  // Skip "@exit"
    int exit_status = atoi(exit_status_str);
    
    // Exit the shell with the provided exit status
    exit(exit_status);
}

void handle_cd_command(const char* command) {
    // Extract the directory path from the command
    const char* directory = command + 3;  // Skip "@cd"
    
    // Change directory using chdir()
    if (chdir(directory) != 0) {
        perror("cd");
    }
}

void handle_env_command(const char* command) {
    // Print the environment variables
    extern char** environ;
    for (char** env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}

void handle_setenv_command(const char* command) {
    // Extract the variable name and value from the command
    const char* variable = command + 7;  // Skip "@setenv"
    const char* value = strchr(variable, ' ');
    if (value == NULL) {
        printf("Invalid format for setenv command.\n");
        return;
    }
    size_t variable_length = value - variable;
    value++;  // Skip the space
    
    // Set the environment variable using setenv()
    if (setenv(variable, value, 1) != 0) {
        perror("setenv");
    }
}

void handle_unsetenv_command(const char* command) {
    // Extract the variable name from the command
    const char* variable = command + 9;  // Skip "@unsetenv"
    
    // Unset the environment variable using unsetenv()
    if (unsetenv(variable) != 0) {
        perror("unsetenv");
    }
}

void handle_alias_command(const char* command) {
    // Extract the alias name and value from the command
    const char* alias = command + 6;  // Skip "@alias"
    const char* value = strchr(alias, ' ');
    if (value == NULL) {
        printf("Invalid format for alias command.\n");
        return;
    }
    size_t alias_length = value - alias;
    value++;  // Skip the space
    
    // Store or process the alias information as needed
    // (e.g., save it in a data structure, apply it to subsequent commands)
}
