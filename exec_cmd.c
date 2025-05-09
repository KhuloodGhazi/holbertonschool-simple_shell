#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * search_path_dirs - Searches for a command in PATH directories.
 * @path_env: The PATH string (colon-separated).
 * @command: The command to search for.
 *
 * Return: Full path if found, NULL otherwise.
 */
char *search_path_dirs(char *path_env, char *command)
{
char *path_copy, *dir;
char full_path[1024];

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
 * find_command_path - Finds the full path of a command.
 * @command: The command name.
 *
 * Return: Full path string, or NULL if not found.
 */
char *find_command_path(char *command)
{
int i = 0;
char *path_env = NULL;

/* Allow absolute and relative paths like ./cmd or ../cmd */
if (command[0] == '/' ||
strncmp(command, "./", 2) == 0 ||
strncmp(command, "../", 3) == 0)
{
if (access(command, X_OK) == 0)
return (strdup(command));
else
return (NULL);
}

while (environ[i])
{
if (strncmp(environ[i], "PATH=", 5) == 0)
{
path_env = environ[i] + 5;
break;
}
i++;
}

if (!path_env || strlen(path_env) == 0)
return (NULL);

return (search_path_dirs(path_env, command));
}

/**
 * handle_builtins - detect and run built‑in commands (exit, env)
 * @args: NULL‑terminated argv array
 * Return: -1 for “exit”, 0 for “env”, or -2 if not a builtin
 */
static int handle_builtins(char **args)
{
int i;
if (strcmp(args[0], "exit") == 0)
return (-1);

if (strcmp(args[0], "env") == 0)
{
for (i = 0; environ[i]; i++)
puts(environ[i]);
return (0);
}
return (-2);
}

/**
 * launch_external - fork, execve a binary, and wait for it
 * @path: full path to executable
 * @args: NULL‑terminated argv array
 * Return: child's exit code or 127 on failure
 */
static int launch_external(char *path, char **args)
{
pid_t pid;
int status;

pid = fork();
if (pid == -1)
{
perror("fork");
return (127);
}

if (pid == 0)
{
execve(path, args, environ);
perror("./hsh");
exit(127);
}

waitpid(pid, &status, 0);
if (WIFEXITED(status))
return (WEXITSTATUS(status));
return (2);
}

/**
 * execute_command - Forks and executes a command if it exists.
 * @args: NULL-terminated array of command arguments.
 *
 * Return: 0 on success, 127 if command not found or error.
 */
int execute_command(char **args)
{
char *cmd_path;
int rc;

if (!args || !args[0])
return (0);

/* Try builins */
rc = handle_builtins(args);
if (rc != -2)
return (rc);

/* Locate in PATH */
cmd_path = find_command_path(args[0]);
if (!cmd_path)
{
fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
return (127);
}

/* Fork/exec and collect exit code */
rc = launch_external(cmd_path, args);
free(cmd_path);
return (rc);
}
