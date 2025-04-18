#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "simpleshell.h"

#define MAX_ARGS 64

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
 * execute_command - Forks and executes the command
 * @args: array of arguments
 */
void execute_command(char **args)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        if (execve(args[0], args, NULL) == -1)
            perror("./hsh");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        wait(NULL);
    }
    else
    {
        perror("fork");
    }
}

/**
 * print_env - prints the environment
 * Return: zero
 */
int print_env(void)
{
    int i = 0;

    if (env == NULL)
        return (-1);
    while (env[i])
    {
        printf("%s\n", env[i++]);
    }
    return (0);
}

/**
 * parse - tokenizes
 * @command: command from the user
 * @envp: enviroment path
 */
void parse(char command[], char **envp)
{
    char *arguments[11];
    char *token = strtok(command, " ");
    int arg_count = 0;

    while (token != NULL && arg_count < 10)
    {
        arguments[arg_count++] = token;
        token = strtok(NULL, " ");
    }
    if (arg_count > 11)
    {
        perror("Error: Too many arguments");
        return;
    }
    arguments[arg_count] = NULL;
    if (arg_count > 0)
    {
        if (envp != NULL)
            execute(arguments, envp);
        else
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", arguments[0]);
            exit(127);
        }
    }
}

/**
 * input - function to keep prompting user until exit
 * @command: argument to process
 * @size: size of argument
 */
void input(char **command, size_t *size)
{
    size_t read_bytes;

    read_bytes = getline(command, size, stdin);
    if ((int) read_bytes == EOF)
    {
        if (isatty(STDIN_FILENO) != 0)
            printf("\n");
        if (*command != NULL)
            free(*command);
        exit(EXIT_SUCCESS);
    }
    if ((*command)[read_bytes - 1] == '\n')
        (*command)[read_bytes - 1] = '\0';
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
            if (args[0] != NULL)
                execute_command(args);
            free(args);
        }
    }

    free(line);
    return (0);
}
