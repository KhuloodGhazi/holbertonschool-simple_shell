#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

#define MAX_ARGS 64

/**
 * main - Entry point of the simple shell.
 *
 * Return: Always 0 (Success).
 */
int main(void)
{
int status, last_status = 0;

while (1)
{
status = handle_input();
if (status == -1)
break;
if (status == 127)
exit(127);
last_status = status;
}
return (last_status);
}

/**
 * handle_input - Reads, processes, and executes user input.
 *
 * Return: 0 on success, -1 on EOF or error, 127 if command not found.
 */
int handle_input(void)
{
char *input = NULL;
size_t len = 0;
ssize_t read;
char *args[MAX_ARGS];
char *token;
int i, status;

if (isatty(STDIN_FILENO))
printf(":) ");

read = getline(&input, &len, stdin);
if (read == -1)
{
free(input);
return (-1);
}

if (input[read - 1] == '\n')
input[read - 1] = '\0';

if (strlen(input) == 0)
{
free(input);
return (0);
}

token = strtok(input, " ");
i = 0;
while (token != NULL && i < MAX_ARGS - 1)
{
args[i++] = token;
token = strtok(NULL, " ");
}
args[i] = NULL;

status = execute_command(args);
free(input);
return (status);
}
