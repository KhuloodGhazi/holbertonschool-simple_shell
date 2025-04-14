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

write(STDOUT_FILENO, "#cisfun$ ", 9);
nread = getline(line, len, stdin);
if (nread == -1)
{
free(*line);
write(STDOUT_FILENO, "\n", 1);
exit(0);
}
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

pid = fork();
if (pid == 0)
{
argv[0] = line;
argv[1] = NULL;

if (execve(argv[0], argv, NULL) == -1)
perror("./hsh");
exit(0);
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

while (1)
{
prompt_and_read(&line, &len);
execute_command(line);
}

free(line);
return (0);
}
