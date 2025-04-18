#ifndef MAIN_H
#define MAIN_H

extern char **environ;

int execute_command(char **args);
int handle_input(void);
char *find_command_path(char *command);

#endif /* MAIN_H */
