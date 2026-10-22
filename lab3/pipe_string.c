#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int pipefds[2];
    char buffer[5];

    if (pipe(pipefds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    char *pin = "4128\0";

    printf("writing pin to pipe...\n");
    write(pipefds[1], pin, 5);
    printf("done.\n\n");

    printf("reading pin from pipe...\n");
    read(pipefds[0], buffer, 5);
    printf("done.\n\n");

    printf("pin from pipe: %s\n", buffer);

    return 0;
}
