#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * prompt_and_read - Displays prompt and reads a line from stdin
 * @line: pointer to buffer
 * @len: pointer to buffer size
 *
 * Return: Number of characters read
 */
ssize_t prompt_and_read(char **line, size_t *len)
{
ssize_t nread;

/* Only show prompt in interactive mode */
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "#cisfun$ ", 9);

/* Read line from stdin */
nread = getline(line, len, stdin);
if (nread == -1)
{
/* Handle Ctrl+D (EOF): free memory and exit */
free(*line);
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "\n", 1);
exit(0);
}

/* Remove trailing newline */
if ((*line)[nread - 1] == '\n')
(*line)[nread - 1] = '\0';

return (nread);
}

/**
 * execute_command - Forks and executes the command
 * @line: command to execute
 */
void execute_command(char *line)
{
pid_t pid;
char *argv[2];

/* Create child process */
pid = fork();
if (pid == 0)
{
/* In child: prepare arguments and execute command */
argv[0] = line;
argv[1] = NULL;

/* Execute the command (must be full path) */
if (execve(argv[0], argv, NULL) == -1)
perror("./hsh");

/* Exit child if execve fails */
exit(0);
}
else if (pid > 0)
{
/* In parent: wait for child process */
wait(NULL);
}
else
{
/* Handle fork error */
perror("fork");
}
}

/**
 * main - Entry point of the shell
 * Return: Always 0
 */
int main(void)
{
char *line = NULL;
size_t len = 0;

/* Shell loop: keeps running until user exits */
while (1)
{
/* Show prompt and read input */
prompt_and_read(&line, &len);

/* Execute the input command */
execute_command(line);
}

free(line);
return (0);
}
