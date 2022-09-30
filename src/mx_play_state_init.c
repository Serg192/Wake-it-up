#include "../inc/endgame.h"

void mx_play_state_init(t_app_global *app) {
    Mix_PlayMusic(app->res->level_music, -1);
    
    SDL_Rect pos = {0, 0, TILE_WIDTH, TILE_HEIGHT};
    SDL_Rect fade = {0, 0, WIN_WIDTH, WIN_HEIGHT};
    SDL_Rect leave_btn_pos = {WIN_WIDTH - 108, WIN_HEIGHT - 40, 90, 30};
    SDL_Rect ret_btn_pos = {WIN_WIDTH - 224, WIN_HEIGHT - 40, 90, 30};
    SDL_Rect ui_panel = {WIN_WIDTH - 245, WIN_HEIGHT - 50, 245, 50}; 
    t_play_state_data *context = malloc(sizeof(t_play_state_data));
    context->level = mx_get_saved_level(app);
    if (app->current_level > 6) {
    	context->level->entities[1].activated = true;
    }
    context->tile_pos = pos;
    context->ret_btn_pos = ret_btn_pos;
    context->leave_btn_pos = leave_btn_pos;
    context->ui_panel = ui_panel;
    context->alpha = 0xff;
    context->fade_rec_pos = fade;
    context->sound_was_played = false;
    app->context = context;
}

