#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void askName(int num) {
    char name[100];
    printf("child %d (pid: %d), enter your name: ", num, getpid());
    scanf("%99s", name);
    printf("hello %s\n\n", name);
}

int main() {
    for (int i = 1; i <= 4; i++) {
        int pid = fork();

        if (pid == 0) {
            askName(i);
            exit(0);
        } else {
            wait(NULL);
        }
    }

    printf("job is done\n");
    return 0;
}
