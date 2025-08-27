// tests/gnl_cat.c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        return 2;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 3;
    }
    char *s;
    while ((s = get_next_line(fd)) != NULL) {
        // get_next_line satırı \n’li veriyorsa aynen basıyoruz
        // son satır \n'sizse de aynen (printf %s zaten newline eklemez)
        printf("%s", s);
        free(s);
    }
    close(fd);
    return 0;
}
