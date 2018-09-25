/*
Write a program that will utilize signal handlers to 
intercept keyboard interrupts to manage control of a
child process.

- [ ] Your main program should fork and exec a 
new child process to run the “yes” command (use
man yes to learn more).
- [ ] You should then register signal 
handlers for both ctrl-c and ctrl-z in your main
program.
- [ ] The ctrl-z signal handler should toggle the 
child yes stop the child process if it is running, or
resume the child process if it is stopped, all while 
keeping the main program running.
- [ ] The ctrl-c signal
should kill the child process, and then exit the main 
process.
- [ ] In both signal handlers, add print statements
indicating what the program is doing – i.e. “ctrl-z 
caught, stopping child process”. Your main program
should sit in an infinite loop once the setup has been 
completed. 
- [ ] It should only exit when the user hits ctrl-
c, after cleaning up the child process.
*/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    pid_t childID;
    childID = fork();
    
    if (childID == -1) {
        /* failure code */
    } else if (childID == 0) {
        /* child code */
        char *args[] = {"yes"};
        char *env[] = { 0 };
        execve("yes", args, env);
        perror("execvs yes failed.");
        exit(1);
    } else {
        /* parent code */
        kill(childID, 9);
    }
    return 0;
}
