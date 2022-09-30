#include "../inc/endgame.h"

static inline void define_level(t_app_global * app, char *buffer) {

    char *current = strtok(buffer, "/");
    char *prev = current;

    while(current != NULL) {

        prev = current;
        current = strtok(NULL, "/");
    }

    app->current_level = atoi(prev);
}

t_level *mx_get_saved_level(t_app_global *app) {
    int index = 0;
    char buffer[64];
    char c; 
    int fd = open("resource/levels/save", O_RDONLY); 
   
    while(read(fd, &c, 1)) {
        if(c == '\n' || c == '\t' || c == '\r' || c == '\f' || c == ' ')
            break;
        buffer[index++] = c;
    } 
    buffer[index] = '\0';
    close(fd);
    t_level *level = mx_parse_level(buffer);
    
    define_level(app, buffer);
    return level;
}

