#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int sig) {
    if (sig == SIGINT) {
        printf("\nthis is a special signal handler for sigint\n");
    } else if (sig == SIGTSTP) {
        printf("\nthis is a special signal handler for sigtstp\n");
    } else if (sig == SIGQUIT) {
        printf("\nthis is a special signal handler for sigquit\n");
    }
}

int main(void) {
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);
    signal(SIGQUIT, signal_handler);

    printf("program running. press ctrl+c, ctrl+z, or ctrl+\\ to test signals.\n");
    printf("press ctrl+d to exit.\n\n");

    char s[100];
    while (fgets(s, sizeof(s), stdin) != NULL) {
    }

    return 0;
}
