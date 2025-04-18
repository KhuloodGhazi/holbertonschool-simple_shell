#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * find_command_path - Searches for the full path of a command in the PATH.
 * @command: The name of the command to search for.
 *
 * Return: A malloc'd string containing the full path if found, or NULL.
 *
 * If command is already executable (e.g., /bin/ls), it is returned as is.
 * Otherwise, this function tokenizes PATH variable & checks each directory.
 */
char *find_command_path(char *command)
{
char *path_env, *path_copy, *dir;
char full_path[1024];

if (access(command, X_OK) == 0)
return (strdup(command));

path_env = getenv("PATH");
if (!path_env)
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
 * This function first searches for the command using find_command_path().
 * If not found, it prints an error and returns.
 * If found, it forks a child process to run execve().
 * The parent waits for the child to finish.
 */
void execute_command(char **args)
{
pid_t pid;
char *cmd_path;

cmd_path = find_command_path(args[0]);
if (!cmd_path)
{
fprintf(stderr, "%s: command not found\n", args[0]);
return;
}

pid = fork();
if (pid == -1)
{
perror("fork");
free(cmd_path);
return;
}
if (pid == 0)
{
if (execve(cmd_path, args, environ) == -1)
{
perror("execve");
exit(EXIT_FAILURE);
}
}
else
{
wait(NULL);
}

free(cmd_path);
}
