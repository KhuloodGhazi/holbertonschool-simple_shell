#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

/* Function prototype */
void execute_command(char **args);

/**
 * main - Entry point of the simple shell.
 *
 * Return: Always 0 (Success).
 *
 * The shell reads input from the user, tokenizes it into arguments,
 * and calls execute_command() to run the command.
 */
int main(void)
{
char input[MAX_INPUT];
char *args[MAX_ARGS];
char *token;
int i;

while (1)
{
printf(":) ");
if (!fgets(input, MAX_INPUT, stdin))
break;

/* Remove newline character from input */
input[strcspn(input, "\n")] = '\0';

/* Skip empty lines */
if (strlen(input) == 0)
continue;

/* Tokenize input into command and arguments */
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

return (0);
}
