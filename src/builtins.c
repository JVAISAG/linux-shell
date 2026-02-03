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

void builtin_help(void) {
    puts("Mini Shell - built-in commands:");
    puts("  cd <dir>      Change the current directory");
    puts("  pwd           Print the current working directory");
    puts("  export NAME=VALUE");
    puts("                Set an environment variable");
    puts("  unset NAME    Remove an environment variable");
    puts("  env           Print environment variables");
    puts("  help          Show this help message");
    puts("  exit          Exit the shell");
}


int is_valid_identifier(const char *s) {
    if (!s || !s[0])
        return 0;

    // first character: letter or _
    if (!(isalpha(s[0]) || s[0] == '_'))
        return 0;

    // remaining characters
    for (int i = 1; s[i]; i++) {
        if (!(isalnum(s[i]) || s[i] == '_'))
            return 0;
    }

    return 1;
}

int handle_builtin(char **argv){
     if(strcmp(argv[0],"cd") == 0){
           if(argv[1] == NULL){
            fprintf(stderr,"cd: missing arguments\n");
           
           }
           else{
            if(chdir(argv[1]) != 0){
                perror("cd");
            }
           }
           return 1;
        }

        
        //implementing pwd as a builtin can make it faster cus no fork() and exec just getcwd()
        if(strcmp(argv[0],"pwd") == 0){

           char *buf;
           long int size;
           char *ptr;
           
           size = pathconf(".",_PC_PATH_MAX);
           buf = (char*)malloc((size_t)size);

           if(buf != NULL){
            ptr = getcwd(buf,size);
            printf("%s\n",ptr);
           }else{
            perror("getcwd");
           }

           free(buf);
           return 1;
        }


        if(strcmp(argv[0],"export") == 0){
           

            if(!argv[1]){
                fprintf(stderr,"export: missing argument\n");
                
            }
            
            char *eq = strchr(argv[1],'=');

            if(!eq){
                fprintf(stderr,"export: syntax error use:(NAME=VALUE)\n");
            }

            *eq = '\0';

            char *name = argv[1];
            char *value = eq + 1;

            if(!is_valid_identifier(name)){
                fprintf(stderr,"Invalid naming scheme: fisrt character should be a letter or _");
                
            }

            if(setenv(name,value,1) == -1){
                perror("setenv");
            }

            return 1;
        }

        if(strcmp(argv[0],"unset") == 0){
            if(!argv[1]){
                fprintf(stderr,"unset: missing argument");
            }
            
            for (int i = 1; argv[i] != NULL; i++) {
                if (unsetenv(argv[i]) == -1) {
                    perror("unsetenv");
                }
            }
           return 1;
        }

        if(strcmp(argv[0],"help") == 0){
            builtin_help();
            return 1;
        }

        extern char **__environ;
        
        if(strcmp(argv[0],"env") == 0){
            for(char** e = __environ;*e;e++){
                printf("%s\n",*e);
            }
            return 1;
        }

        if(strcmp(argv[0],"exit") == 0){
            exit(0);
        }
        return 0;
}