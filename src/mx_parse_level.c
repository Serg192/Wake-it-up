#include "../inc/endgame.h"

static void parse_entities(t_level *level, int fd) {
    char c;
    char buffer[64];
    int index = 0;
    char *token;
    while(read(fd, &c, 1))
        buffer[index++] = c;
    buffer[index] = '\0';
    index = 0;
    token = strtok(buffer, "\n");
    level->entity_count = atoi(token);
    level->entities = malloc(sizeof(t_entity) * level->entity_count);

    for(int i = 0 ; i < level->entity_count; i++) {
        t_entity entity;
        if(i == 0)
            entity.activated = true;
        else
            entity.activated = false;
        token = strtok(NULL, "\n");
        entity.x_pos = atoi(token);
        token = strtok(NULL, "\n");
        entity.y_pos = atoi(token);
        level->entities[index++] = entity;
    }
}

t_level *mx_parse_level(const char *level_path) {
    t_level *level = malloc(sizeof(t_level));
    int fd = open(level_path, O_RDONLY);
    char c;


    level->tiles = (int**)malloc(sizeof(int*) * LEVEL_HEIGHT);
    for(int i = 0; i < LEVEL_HEIGHT; i++)
       level->tiles[i] = (int*)malloc(sizeof(int) * LEVEL_WIDTH);

    for(int i = 0; i < LEVEL_HEIGHT; i++) {
        for(int j = 0; j < LEVEL_WIDTH; j++) {
            read(fd, &c, 1);
            level->tiles[i][j] = atoi(&c);
        }
        read(fd, &c, 1);
    }

    parse_entities(level, fd);
    close(fd);
    return level;
}

