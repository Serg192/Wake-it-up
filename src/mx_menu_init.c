#include "../inc/endgame.h"

void mx_menu_init(t_app_global *app) {
    const int pix_per_l = 20;
    Mix_PlayMusic(app->res->menu_music, -1);
    t_menu_data *context = malloc(sizeof(t_menu_data));

    SDL_Rect logo_pos = {WIN_WIDTH / 2 - 320 / 2, 100, 320, 70};
    SDL_Rect start_btn_pos = {WIN_WIDTH / 2 - 8 * pix_per_l / 2, 260, 8 * pix_per_l, 40};    
    SDL_Rect continue_btn_pos = {WIN_WIDTH / 2 - 8 * pix_per_l / 2, 330, 8 * pix_per_l, 40}; 
    SDL_Rect exit_btn_pos = {WIN_WIDTH / 2 - 4 * pix_per_l / 2, 400, 4 * pix_per_l, 40};    
    SDL_Rect bg_pos = {0, 0, WIN_WIDTH, WIN_HEIGHT};
    context->bg_pos = bg_pos;    
    context->logo_pos = logo_pos;
    context->start_btn_pos = start_btn_pos;
    context->continue_btn_pos = continue_btn_pos;
    context->exit_btn_pos = exit_btn_pos;
    context->sound_was_played = false;
    app->context = context;
}

