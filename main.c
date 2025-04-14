#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * trim_spaces - Removes leading and trailing spaces from a string
 * @str: input string
 *
 * Return: pointer to trimmed string
 */
char *trim_spaces(char *str)
{
char *end;

/* Skip leading spaces */
while (*str == ' ' || *str == '\t')
str++;

if (*str == 0)  /* All spaces */
return (str);

/* Remove trailing spaces */
end = str + strlen(str) - 1;
while (end > str && (*end == ' ' || *end == '\t'))
end--;

/* Null terminate the trimmed string */
end[1] = '\0';

return (str);
}

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
 * main - Entry point of the shell
 * Return: Always 0
 */
int main(void)
{
char *line = NULL, *cleaned;
size_t len = 0;

while (1)
{
prompt_and_read(&line, &len);
cleaned = trim_spaces(line);

/* Skip empty input */
if (*cleaned != '\0')
execute_command(cleaned);
}

free(line);
return (0);
}
