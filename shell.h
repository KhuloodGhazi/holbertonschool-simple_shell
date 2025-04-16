#ifndef SHELL_H
#define SHELL_H

void execute_command(char *line, char **argv);
char *trim_spaces(char *str);
ssize_t prompt_and_read(char **line, size_t *len);

#endif                     
