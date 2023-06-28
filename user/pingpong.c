#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    // https://www.geeksforgeeks.org/pipe-system-call/
    int p1[2]; // parent to child, [0] read, [1] write
    int p2[2]; // child to parent
    char buffer[1];

    if (pipe(p1) == -1 || pipe(p2) == -1) {
        printf("Pipe create error\n");
    }

    if (fork() == 0) {
        // child process
        close(p1[1]);
        close(p2[0]);
        read(p1[0], buffer, 1);
        printf("%d: received ping\n", getpid());
        write(p2[1], "c", 1);
        close(p1[0]);
        close(p2[1]);
        exit(0);
    } else {
        // parent process
        close(p1[0]);
        close(p2[1]);
        write(p1[1], "p", 1);
        read(p2[0], buffer, 1);
        printf("%d: received pong\n", getpid());
        close(p1[1]);
        close(p2[0]);
        exit(0);
    }
}
