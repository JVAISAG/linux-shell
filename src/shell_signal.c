#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "shell_signal.h"


pid_t fg_pid = -1;

void sigchld_handler(int signo){
    (void) signo;

    while(waitpid(-1,NULL,WNOHANG) > 0){
        //nothing
    }
}


void sigint_handler(int signo){
    (void)signo;

    if(fg_pid > 0){
        kill(fg_pid,SIGINT);
    }
}

void setup(void){
    struct sigaction sa;    
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    sigaction(SIGCHLD,&sa,NULL);

    struct sigaction si;
    si.sa_handler = sigint_handler;
    sigemptyset(&si.sa_mask);
    si.sa_flags = SA_RESTART;

    sigaction(SIGINT,&si,NULL);
}