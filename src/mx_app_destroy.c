#include "../inc/endgame.h"

void mx_app_destroy(t_app_global *global) {
    SDL_DestroyRenderer(global->renderer);
    SDL_DestroyWindow(global->window);
    Mix_FreeMusic(global->res->menu_music);
    Mix_FreeMusic(global->res->level_music);
    Mix_FreeChunk(global->res->join_sound);
    Mix_FreeChunk(global->res->slide_sound);
    Mix_FreeChunk(global->res->select_sound);
    Mix_FreeChunk(global->res->portal_sound);
    SDL_DestroyTexture(global->res->move_here);
    SDL_DestroyTexture(global->res->ground);
    SDL_DestroyTexture(global->res->wall);
    SDL_DestroyTexture(global->res->portal);
    SDL_DestroyTexture(global->res->main_block);
    SDL_DestroyTexture(global->res->additional_block);
    SDL_DestroyTexture(global->res->logo_tex);
    SDL_DestroyTexture(global->res->start_btn_tex);
    SDL_DestroyTexture(global->res->continue_btn_tex);
    SDL_DestroyTexture(global->res->exit_btn_tex);
    SDL_DestroyTexture(global->res->retry_btn_tex);
    SDL_DestroyTexture(global->res->leave_btn_tex);
    SDL_DestroyTexture(global->res->menu_bg_tex);
    TTF_CloseFont(global->res->monocraft_fnt);
}

