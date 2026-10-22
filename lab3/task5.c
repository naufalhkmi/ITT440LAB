#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sigint_handler(int sig) {
    printf("\nsigint signal received. exit program.\n");
    exit(0);
}

int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main(void) {
    signal(SIGINT, sigint_handler);

    int pipefds[2];
    if (pipe(pipefds) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        close(pipefds[0]);

        int num;
        printf("child: enter a number: ");
        scanf("%d", &num);

        write(pipefds[1], &num, sizeof(num));
        close(pipefds[1]);
        exit(0);
    } else {
        close(pipefds[1]);
        wait(NULL);

        int received_num;
        read(pipefds[0], &received_num, sizeof(received_num));
        close(pipefds[0]);

        printf("parent: received number %d from child\n", received_num);
        if (is_prime(received_num)) {
            printf("parent: %d is a prime number\n", received_num);
        } else {
            printf("parent: %d is not a prime number\n", received_num);
        }
    }

    return 0;
}
