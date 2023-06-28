#include "kernel/types.h"
#include "user/user.h"

void prime(int *p_left) {
    int num;
    int p_right[2];
    if (read(p_left[0], &num, 4) == 0) {
        exit(0);
    } else {
        printf("prime %d\n", num);
    }
    pipe(p_right);
    if (fork() == 0) {
        close(p_right[1]);
        prime(p_right);
        close(p_right[0]);
    } else {
        close(p_right[0]);
        int next;
        // 2,3,4,5,6,7,8,9,10,11: prints 2 and eliminates the multiples of 2
        // => 3, 5, 7, 9, 11: prints 3 and eliminates the multiples of 3
        // => 5, 7, 11: prints 5 and eliminates the multiples of 5
        // => 7, 11: prints 7 and eliminates the multiples of 7
        // => 11: prints 11 and eliminates the multiples of 11
        while (read(p_left[0], &next, 4)) {
            if (next % num != 0) {
                write(p_right[1], &next, 4);
            }
        }
        close(p_right[1]);
        wait(0);
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    int p[2];
    pipe(p);
    if (fork() > 0) {
        close(p[0]);
        for (int i = 2; i <= 35; i++) {
            write(p[1], &i, 4);
        }
        close(p[1]);
        wait(0);
        exit(0);
    } else {
        close(p[1]);
        prime(p);
        close(p[0]);
        exit(0);
    }
}

