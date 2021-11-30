#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#define TRUE 0
#define FALSE 1

int main(int argc, char *argv[]){
    char commands[6][100]; // 2d array to hold the commands
    int arguments[100] = {0}; // int array to keep track of of number of arguments
    char temp[100];
    char *token;
    int i;
    int j = 0; // counter to keep track of how many commands exist
    int k = 0; // counter to track number of arugments for the arguments int array
    int current = FALSE; // boolean variable to determine whether the loop below should concat or copy a string. Example: ls -al : (2 different strings, one command must be concated)
    long pid;

    // loops through command line arguments and parses the commands into the commands 2d string array
    for(i = 1; i < argc; i++){
        if(strcmp(argv[i], ":") != TRUE){
            if(current == TRUE){
                strcat(temp, " ");
                strcat(temp, argv[i]); 
            }
            else{
                strcpy(temp, argv[i]);
                current = TRUE;
            }
            arguments[j] += 1;
        }
        else{
            strcpy(commands[j], temp);
            j++;
            current = FALSE;
        }
    }
    strcpy(commands[j], temp);
    j++;

    for(i = 0; i < j; i++){
        pid = fork();
        switch(pid){
            case -1:
                printf("fork failed: %s\n", strerror(errno));
                break;
            case 0:;
                char tokens[arguments[i]][100];
                k = 0;
                token = strtok(commands[i], " ");
                strcpy(tokens[k], token);
                k++;
                if(arguments[i] > 1){
                    while(token != NULL){
                        token = strtok(NULL, " ");
                        if(token != NULL){
                            strcpy(tokens[k], token);
                            k++;
                        }
                    }
                }
                printf("PID: %ld, PPID: %ld, CMD: %s\n", (long) getpid(), (long) getppid(), commands[i]);
                int g;
                char *p[100];
                for(g = 0; g < arguments[i]; g++){
                    p[g] = tokens[g];
                }
                p[g] = NULL;
                execvp(tokens[0], p);
                break;
        }
    }
    long waitPID;
    int exitStatus = 0;
    while(waitPID = wait(&exitStatus) != -1){
        if(waitPID == -1){
            printf("wait error: %s\n", strerror(errno));
        }
        if(exitStatus != 0){
            printf("Child terminated normally: %d\n", WEXITSTATUS(exitStatus));
        }
        if(WIFSIGNALED(exitStatus) != 0){
            printf("Child terminated due to uncaught signal: %d\n", WTERMSIG(exitStatus));
        }
    }
    return 0;
}
