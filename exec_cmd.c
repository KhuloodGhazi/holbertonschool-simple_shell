#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * find_command_path - Searches for the full path of a command using PATH.
 * @command: The name of the command to search for.
 *
 * Return: A malloc'd string with the full path, or NULL if not found.
 */
char *find_command_path(char *command)
{
char *path_env = NULL, *path_copy, *dir;
char full_path[1024];
int j = 0;

if (access(command, X_OK) == 0)
return (strdup(command));

while (environ[j])
{
if (strncmp(environ[j], "PATH=", 5) == 0)
{
path_env = environ[j] + 5;
break;
}
j++;
}

if (!path_env || strlen(path_env) == 0)
return (NULL);

path_copy = strdup(path_env);
if (!path_copy)
return (NULL);

dir = strtok(path_copy, ":");
while (dir)
{
snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
if (access(full_path, X_OK) == 0)
{
free(path_copy);
return (strdup(full_path));
}
dir = strtok(NULL, ":");
}
free(path_copy);
return (NULL);
}

/**
 * execute_command - Forks and executes a command if it exists.
 * @args: NULL-terminated array of arguments (command and its parameters).
 *
 * Return: 0 on success, 127 if command not found or failed to execute.
 */
int execute_command(char **args)
{
pid_t pid;
int status;
char *cmd_path;

if (!args || !args[0])
return (0);

cmd_path = find_command_path(args[0]);
if (!cmd_path)
{
fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
return (127);
}

pid = fork();
if (pid == -1)
{
perror("fork");
free(cmd_path);
return (127);
}

if (pid == 0)
{
if (execve(cmd_path, args, environ) == -1)
{
perror("./hsh");
free(cmd_path);
exit(127);
}
}
else
{
wait(&status);
}

free(cmd_path);
return (0);
}
