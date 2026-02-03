#ifndef PARSER_H
#define PARSER_H

int parse_line(char *line,
               char **argv,
               char **input_file,
               char **output_file,
               int *append,
               int *background);

#endif
