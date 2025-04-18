#include "shell.h"

/**
 * execute_cmd - Executes a command with path resolution
 * @args: Argument vector (command and its arguments)
 * Return: 127 if command not found, 0 otherwise
 */
int execute_cmd(char **args)
{
pid_t pid;
int status;
char *cmd_path;

if (args[0] == NULL)
return (0);

if (strcmp(args[0], "exit") == 0)
exit(0);

/* Built-in: env */
if (strcmp(args[0], "env") == 0)
{
int i = 0;
while (environ[i])
printf("%s\n", environ[i++]);
return (0);
}

/* Check if command contains '/' */
if (strchr(args[0], '/'))
{
if (access(args[0], X_OK) == 0)
cmd_path = strdup(args[0]);
else
{
fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
return (127);
}
}
else
{
/* No '/', resolve using PATH */
cmd_path = find_command(args[0]);
if (cmd_path == NULL)
{
fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
return (127);
}
}

/* Fork and exec */
pid = fork();

if (pid == 0)
{
if (execve(cmd_path, args, environ) == -1)
{
fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
free(cmd_path);
exit(127);
}

}
else if (pid < 0)
{
perror("fork");
}
else
{
if (waitpid(pid, &status, 0) != -1)
{
if (WIFEXITED(status))
{
int exit_status = WEXITSTATUS(status);
free(cmd_path);
return (exit_status);
}
}
free(cmd_path);
return (2);
}
return (0);
}
