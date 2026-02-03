#ifndef SHELL_SIGNAL_H
#define SHELL_SIGNAL_H

#include <sys/types.h> /* for pid_t */
#include <signal.h>

extern pid_t fg_pid;

void sigchld_handler(int signo);
void sigint_handler(int signo);
void setup(void);

#endif /* SHELL_SIGNAL_H */