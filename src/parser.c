#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include<fcntl.h>
#include<signal.h>

#define MAX_ARG 64

int parse_line(char *line,
               char **argv,
               char **input_file,
               char **output_file,
               int *append,
               int *background){
                
        char *saveptr = NULL;
        char *token = strtok_r(line," ",&saveptr);
        int argc = 0;
        
        while(token != NULL && argc < MAX_ARG - 1){
            
            if(strcmp(token,">") == 0){
                token = strtok_r(NULL," ",&saveptr);
                *output_file = token;
                *append = 0;
            }

            else if(strcmp(token,">>") == 0){
                token = strtok_r(NULL," ",&saveptr);
                *output_file = token;
                *append = 1;
            }

            else if(strcmp(token,"<") == 0){
                token = strtok_r(NULL," ",&saveptr);
                *input_file = token;
            }

            else if(strcmp(token,"&") == 0){
                *background = 1;
            }
            
            else{
                argv[argc++] = token;
            }
            token = strtok_r(NULL," ",&saveptr);
        }

        argv[argc] = NULL;


          
        return argc;
    }
