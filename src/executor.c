#define POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include<fcntl.h>
#include<signal.h>

#include "executor.h"
#include "shell_signal.h"

void execute_command(char **argv,
                     char *input_file,
                     char *output_file,
                     int append,
                     int background){
                        
        pid_t pid = fork();

        //child process
        if(pid == 0){
            if(output_file){
                int flags = O_WRONLY | O_CREAT | ((append == 1) ? O_APPEND : O_TRUNC); 
                int fd = open(output_file,flags,0644);
                
                if(fd < 0){
                    perror("open");
                    exit(1);
                }
                dup2(fd,STDOUT_FILENO);
                close(fd);
            }

            if(input_file){
                int fd = open(input_file,O_RDONLY);

                if(fd<0){
                    perror("open");
                    exit(1);
                }

                dup2(fd,STDIN_FILENO);
                close(fd);
            }

            execvp(argv[0],argv);
            perror("execvp");
            exit(1);
        }

        //parent
        if(pid > 0){
            if(!background){
                fg_pid = pid;
                waitpid(pid,NULL,0);
                fg_pid = 1;
            }else{
                printf("[bg] pid %d\n", pid);
            }
        }

        //if fork fails
        if(pid == -1){
            perror("fork");
        }

        
    }
                     