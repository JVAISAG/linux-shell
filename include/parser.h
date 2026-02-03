#ifndef PARSER_H
#define PARSER_H

int parse_line(char *line,
               char **argv,
               char **pipe_argv,
               int *has_pipe,
               char **input_file,
               char **output_file,
               int *append,
               int *background);

extern int has_pipe;
extern char **pipe_argv;
            

#endif
