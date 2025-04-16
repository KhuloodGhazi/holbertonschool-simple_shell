TASK 3
==
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64

/**
 * split_line - Splits a line into arguments (tokens)
 * @line: input command line
 *
 * Return: NULL-terminated array of strings
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
 * prompt_and_read - Shows prompt and reads line
 * @line: pointer to buffer
 * @len: pointer to buffer size
 *
 * Return: number of chars read
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
 * execute_command - Forks and executes a command with arguments
 * @args: NULL-terminated array of arguments
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
 * main - Entry point
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

  if (nread > 1) /* skip empty/whitespace lines */
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
