// tests/gnl_multi.c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "usage: %s <file1> <file2> [file3]\n", argv[0]);
        return 2;
    }
    int fds[3] = {-1,-1,-1};
    int n = argc - 1;
    if (n > 3) n = 3;
    for (int i = 0; i < n; i++) {
        fds[i] = open(argv[i+1], O_RDONLY);
        if (fds[i] < 0) { perror("open"); return 3; }
    }
    int alive = n;
    int turn = 0;
    while (alive) {
        int i = turn % n;
        if (fds[i] >= 0) {
            char *s = get_next_line(fds[i]);
            if (s) {
                // hangi fd’den geldiğini göstermek için prefix (gözle kontrol)
                printf("[fd%d]%s", i, s);
                free(s);
            } else {
                close(fds[i]);
                fds[i] = -1;
                alive--;
            }
        }
        turn++;
    }
    return 0;
}
