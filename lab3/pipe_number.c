#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int pipefds[2];
    int buffer;

    if (pipe(pipefds) == -1) {
        perror("pipe");
        exit(1);
    }

    int nombor = 22;

    printf("writing a number to pipe...\n");
    write(pipefds[1], &nombor, sizeof(nombor));
    printf("done.\n\n");

    printf("reading a number from pipe...\n");
    read(pipefds[0], &buffer, sizeof(buffer));
    printf("done.\n\n");

    printf("number from pipe: %d\n", buffer);

    return 0;
}
