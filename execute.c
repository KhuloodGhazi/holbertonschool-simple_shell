#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include"shell.h"
/**
 * execute_command - Forks and executes a command from the user input
 * @line: the command line to execute (path to executable)
 *
 * Description: This function parses the input line, prepares the argument
 * array, then creates a child process that runs the given command.
 * It waits for the child to finish before continuing.
 *
 * Return: Nothing (void)
 */
void execute_command(char *line, char **argv)
{
char *args[64];
char *token;
inti = 0;
pid_tpid;

token = strtok(line, "\t");
while (token != NULL && i < 63)
{
args[i++] = token;
token = strtok(NULL, "\t");
}
args[i] = NULL;
if (args[0] == NULL)
return;
pid = fork();
if (pid == 0)
{
if (execve(args[0], args, environ) == -1)
{
perror(argv[0]);
}
exit(EXIT_FAILURE);
}
else if (pid < 0)
{
perror("fork");
}
else
{
wait(NULL);
}
}
