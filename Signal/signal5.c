#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<wait.h>
#include <unistd.h>

int val = 10;
void handler(int sig){
    val += 5;
    printf("The value is %d ",val);
}
int main(){
    pid_t pid;
    signal(SIGCHLD, handler);
    if ((pid = fork()) == 0)
    {
        val -= 3;
        exit(0);
    }
    waitpid(pid, NULL, 0);
    printf("val = %d\n", val);
    exit(0);
}