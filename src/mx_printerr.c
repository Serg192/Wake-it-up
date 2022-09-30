#include "../inc/endgame.h"

void mx_printerr(const char *err) {
    for(int i = 0; err[i] != '\0'; i++)
        write(2, err + i, 1);
}

