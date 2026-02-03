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
                     char **pipe_argv,
                     int *has_pipe,
                     char *input_file,
                     char *output_file,
                     int append,
                     int background){
                        
       if(*has_pipe ==1){
            pid_t pid1;
            int fd[2];

            if(pipe(fd)== -1){ // opens a file pipe buffer in kernal memory fd[0]->read end  fd[1]->write end
                perror("pipe");
                return;
            }

            pid1 = fork();

            if(pid1 == 0){
                dup2(fd[1],STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);

                execvp(argv[0],argv);
                perror("execvp");
                exit(1);
            }

            pid_t pid2 = fork();

            if(pid2 == 0){
                dup2(fd[0],STDIN_FILENO);

                close(fd[0]);
                close(fd[1]);

                execvp(pipe_argv[0],pipe_argv);
                perror("execvp");
                exit(1);
            }


            close(fd[1]);
            close(fd[0]);

           if (!background) {
                waitpid(pid1, NULL, 0);
                waitpid(pid2, NULL, 0);
            } else {
                printf("[bg] pids %d %d\n", pid1, pid2);
            }

       }else{
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
                fg_pid = -1;
            }else{
                printf("[bg] pid %d\n", pid);
            }
        }

        //if fork fails
        if(pid == -1){
            perror("fork");
        }

        
       }
    }
                     