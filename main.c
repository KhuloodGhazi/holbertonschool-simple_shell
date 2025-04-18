#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define MAX_ARGS 64

/**
 * main - Entry point of the simple shell.
 *
 * Return: Always 0 (Success).
 */
int main(void)
{
char *input = NULL;
size_t len = 0;
ssize_t read;
char *args[MAX_ARGS];
char *token;
int i;

while (1)
{
printf(":) ");
read = getline(&input, &len, stdin);
if (read == -1)
{
free(input);
break;
}

/* Remove newline character */
if (input[read - 1] == '\n')
input[read - 1] = '\0';

/* Skip empty input */
if (strlen(input) == 0)
continue;

/* Tokenize input */
token = strtok(input, " ");
i = 0;
while (token != NULL && i < MAX_ARGS - 1)
{
args[i++] = token;
token = strtok(NULL, " ");
}
args[i] = NULL;

execute_command(args);
}
free(input);
return (0);
}
