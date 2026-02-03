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

#include "builtins.h"
#include "shell_signal.h"
#include "executor.h"
#include "parser.h"


#define MAX_ARG 64

void print_cwd(){
    printf("mini-shell:");
    char *cwd = getcwd(NULL,0);
    
    if(!cwd){
        perror("getcwd");
        return;
    }

    char *home = getenv("HOME");

    if(!home){
        printf("%s",cwd);
        free(cwd);
        return;
    }
    
    size_t home_len = strlen(home);
    
    if(strncmp(cwd,home,home_len) == 0 && (cwd[home_len] == '/' || cwd[home_len] == '\0')){
        if(cwd[home_len] == '\0'){
            printf("~$ ");
        }else{
            printf("~%s$ ",cwd+home_len);
        }
        
    }else{
        printf("~%s$ ",cwd);
    }

    free(cwd);
}


int main(){
    char *argv[MAX_ARG];
    char *pipe_argv[MAX_ARG];
    int   has_pipe = 0;
    char *line = NULL;
    size_t len = 32;

    while(1){

        setup();

        char *output_file = NULL;
        int append = 0;
        char *input_file = NULL;
        int background = 0;

        print_cwd();
        fflush(stdout);
        ssize_t n = getline(&line,&len,stdin);
        
        if(n == -1){
            printf("\n");
            break;
        }

        if(n>0 && line[n-1] == '\n'){
            line[n-1] = '\0';
        }

        for (int i = 0; i < MAX_ARG; i++)
        {
            argv[i] = NULL;
        }
        

        if(parse_line(line,argv,pipe_argv,&has_pipe,&input_file,&output_file,&append,&background) == 0){
            continue;
        }

        if(argv[0] == NULL){
            continue;
        }
        
        if (handle_builtin(argv)) {
            continue;
        }

        execute_command(argv,pipe_argv,&has_pipe,input_file,output_file,append,background);

       

  
    }

    free(line);

    return 0;
}