#ifndef EXECUTOR_H
#define EXECUTOR_H

void execute_command(char **argv,
                     char **pipe_argv,
                     int *has_pipe,
                     char *input_file,
                     char *output_file,
                     int append,
                     int background);

#endif
