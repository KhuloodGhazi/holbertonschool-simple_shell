#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64

extern char **environ;

/**
 * split_line - Splits a line into tokens (arguments)
 * @line: the input line
 *
 * Return: an array of strings (arguments)
 */
char **split_line(char *line)
{
    char **args = malloc(sizeof(char *) * MAX_ARGS);
    char *token;
    int i = 0;

    if (!args)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\n");
    while (token && i < MAX_ARGS - 1)
    {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;

    return (args);
}

/**
 * prompt_and_read - Displays prompt and reads input line
 * @line: pointer to buffer to fill
 * @len: pointer to size of buffer
 *
 * Return: number of characters read
 */
ssize_t prompt_and_read(char **line, size_t *len)
{
    ssize_t nread;

    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "#cisfun$ ", 9);

    nread = getline(line, len, stdin);
    if (nread == -1)
    {
        free(*line);
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "\n", 1);
        exit(0);
    }

    return (nread);
}

/**
 * find_command - Searches for the command in the PATH
 * @cmd: the command name
 *
 * Return: full path if found, otherwise NULL
 */
char *find_command(char *cmd)
{
    char *path, *path_copy, *token, *full_path;
    size_t len;

    if (access(cmd, X_OK) == 0)
        return strdup(cmd);

    path = getenv("PATH");
    if (!path)
        return NULL;

    path_copy = strdup(path);
    if (!path_copy)
        return NULL;

    token = strtok(path_copy, ":");
    while (token)
    {
        len = strlen(token) + strlen(cmd) + 2;
        full_path = malloc(len);
        if (!full_path)
        {
            free(path_copy);
            return NULL;
        }

        snprintf(full_path, len, "%s/%s", token, cmd);

        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return full_path;
        }

        free(full_path);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

/**
 * execute_command - Forks and executes the command
 * @args: array of arguments
 */
void execute_command(char **args)
{
    pid_t pid;
    char *cmd_path = find_command(args[0]);

    if (!cmd_path)
    {
        fprintf(stderr, "./hsh: command not found: %s\n", args[0]);
        return;
    }

    pid = fork();
    if (pid == 0)
    {
        if (execve(cmd_path, args, environ) == -1)
        {
            perror("./hsh");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0)
    {
        wait(NULL);
    }
    else
    {
        perror("fork");
    }

    free(cmd_path);
}

/**
 * handle_exit - Handles the exit condition of the shell
 * @args: array of arguments
 */
void handle_exit(char **args)
{
    if (args[0] && strcmp(args[0], "exit") == 0)
    {
        free(args);
        exit(0);
    }
}

/**
 * main - Entry point of the shell
 *
 * Return: Always 0
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char **args;

    while (1)
    {
        nread = prompt_and_read(&line, &len);

        if (nread > 1)
        {
            args = split_line(line);
            handle_exit(args);  // Handle exit condition
            if (args[0] != NULL)
                execute_command(args);
            free(args);
        }
    }

    free(line);
    return (0);
}
