#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

pid_t childID;
int isChildStopped = 0;

void cHandler (int signum) {
    printf("\nctrl-c caught\nterminating child process\n");
    printf("childID = %d\n", childID);
    kill(childID, SIGTERM);
    printf("exitting\n");
    exit(0);
}

void zHandler (int signum) {
    printf("\nctrl-z caught\n");
    printf("childID = %d\n", childID);
    if (isChildStopped) {
        printf("continuing child process\n");
        kill(childID, SIGCONT);
        isChildStopped = 0;
    } else {
        printf("stopping child process\n");
        kill(childID, SIGTSTP);
        isChildStopped = 1;
    }
}

int main(int argc, char const *argv[]) {
    childID = fork();
    if (childID == -1) {
        /* failure code */
    } else if (childID == 0) {
        /* child code */
        char *args[] = {"yes", NULL};
        execvp("yes", args);
        perror("execvp yes failed.");
        exit(1);
    } else {
        /* parent code */
        struct sigaction cAction, zAction;
        cAction.sa_handler = cHandler;
        zAction.sa_handler = zHandler;
        sigemptyset (&cAction.sa_mask);
        sigemptyset (&zAction.sa_mask);
        cAction.sa_flags = 0;
        zAction.sa_flags = 0;
        sigaction (SIGINT , &cAction, NULL);
        sigaction (SIGTSTP, &zAction, NULL);
        while (1);
    }
    return 0;
}

/*
Write a program that will utilize signal handlers to
intercept keyboard interrupts to manage control of a
child process.

- [x] Your main program should fork and exec a
new child process to run the “yes” command (use
man yes to learn more).
- [x] You should then register signal
handlers for both ctrl-c and ctrl-z in your main
program.
- [x] The ctrl-z signal handler should toggle the
child yes stop the child process if it is running, or
resume the child process if it is stopped, all while
keeping the main program running.
- [x] The ctrl-c signal should kill the child 
process, and then exit the main process.
- [x] In both signal handlers, add print statements
indicating what the program is doing – i.e. “ctrl-z
caught, stopping child process”.
- [x] Your main program should sit in an infinite 
loop once the setup has been completed.
- [x] It should only exit when the user hits ctrl-
c, after cleaning up the child process.

Special keys are interpreted by OS as requests to send signals to the process.
1. Ctrl-C
    - Send signal SIGINT to the running process.
    - By default, SIGINT causes the process to immediately terminate.
2. Ctrl-Z
    - send signal SIGTSTP to the running process.
    - By default, SIGTSTP causes the process to suspend execution.
*/
