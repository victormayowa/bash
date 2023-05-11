#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64
#define MAX_LINE 1024

int main(int argc, char **argv)
{
    char line[MAX_LINE];
    char *args[MAX_ARGS];
    char *token, *saveptr;
    int status;
    pid_t pid;

    // Interactive mode
    if (argc == 1) {
        while (1) {
            printf("$ ");
            if (fgets(line, MAX_LINE, stdin) == NULL)
                break;
            if (line[strlen(line) - 1] == '\n')
                line[strlen(line) - 1] = '\0';
            token = strtok_r(line, ";", &saveptr);
            while (token != NULL) {
                parse_args(token, args);
                execute(args);
                token = strtok_r(NULL, ";", &saveptr);
            }
        }
    }
    // Batch mode
    else if (argc == 2) {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL) {
            perror("Failed to open file");
            exit(EXIT_FAILURE);
        }
        while (fgets(line, MAX_LINE, file) != NULL) {
            if (line[strlen(line) - 1] == '\n')
                line[strlen(line) - 1] = '\0';
            token = strtok_r(line, ";", &saveptr);
            while (token != NULL) {
                parse_args(token, args);
                execute(args);
                token = strtok_r(NULL, ";", &saveptr);
            }
        }
        fclose(file);
    }
    // Incorrect usage
    else {
        fprintf(stderr, "Usage: %s [batch_file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return 0;
}
