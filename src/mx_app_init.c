#include "../inc/endgame.h"

static inline void init_win_and_rend(t_app_global *global) {
    if(SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN, &(global->window),&(global->renderer))) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window and renderer\n");
        exit(0);
    }
    SDL_SetWindowTitle(global->window, "Wake it up");
    SDL_SetRenderDrawBlendMode(global->renderer, SDL_BLENDMODE_BLEND);
}

static inline void init_sdl() {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        exit(0);
    }
}

static inline void init_audio() {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        mx_printerr("SDL_mixer could not initialize! SDL_mixer Error ");
        mx_printerr(Mix_GetError());
        exit(0);
    }
}

void mx_app_init(t_app_global *global) {
    TTF_Init();
    init_sdl();
    init_audio();
    init_win_and_rend(global);
}

