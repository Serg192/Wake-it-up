#include "../inc/endgame.h"

void mx_play_state_destroy(t_app_global *app) {
    t_play_state_data *data = (t_play_state_data*)app->context;

    for(int i = 0; i < LEVEL_HEIGHT; i++) {
        free(data->level->tiles[i]);
    }
    free(data->level->tiles);
    free(data->level->entities);
    free(data->level);
    
    free(app->context);
}

