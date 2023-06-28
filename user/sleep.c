#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc < 1) {
        fprintf(2, "usage: sleep pattern[times]\n");
        exit(1);
    }
//    printf("[0] %s, [1] %s, argc: %d", argv[0], argv[1], argc);
    // argv[0]: sleep, argv[1] is the sleep ticks
    int time = atoi(argv[1]);
    sleep(time);
//    int ret = sleep(time);
//    if (ret != 0) {
//        fprintf(2, "Error in sleep sys_call!\n");
//    }
    exit(0);
}



