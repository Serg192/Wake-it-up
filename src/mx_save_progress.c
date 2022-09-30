#include "../inc/endgame.h"

static inline char* get_level_n(int index) {
    char *levels[] = {"0", "1", "2", "3", "4", "5",
                      "6", "7", "8", "9", "10", "11"};
    return levels[index];
}

void mx_save_progress(int level_n) {
    int fd = open("resource/levels/save", O_WRONLY | O_TRUNC);
    char buffer[64];
    for(int i = 0; i < 64; i++)
        buffer[i] = '\0';
    strcat(buffer, "resource/levels/");
    strcat(buffer, get_level_n(level_n));
    for(int i = 0; buffer[i] != '\0'; i++) {
        write(fd, buffer + i, 1);
    } 
}

