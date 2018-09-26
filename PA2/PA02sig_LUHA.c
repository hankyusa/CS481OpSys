/*
CS 481 Programming Assignment 2
By Luke Hanks
*/
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
