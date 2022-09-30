#include "../inc/endgame.h"

static SDL_Texture* load_texture(t_app_global *app, const char *path) {
    SDL_Surface *surface = SDL_LoadBMP(path);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(app->renderer, surface);
    SDL_FreeSurface(surface);
    return tex;
}

static SDL_Texture* create_text_texture(const char *text, t_app_global *app, SDL_Color color, TTF_Font *fnt) {
    SDL_Surface *text_surf = TTF_RenderText_Solid(fnt, text, color);
    SDL_Texture *text_tex = SDL_CreateTextureFromSurface(app->renderer, text_surf);
    SDL_FreeSurface(text_surf);
    return text_tex;
}

void mx_load_res(t_app_global *app, t_res *res) {
    SDL_Color white = {0xff, 0xff, 0xff, 0xff};
    SDL_Color grey = {0xda, 0xda, 0xda, 0xda};
    //Textures
    res->move_here = load_texture(app, "resource/img/move_here.bmp");
    res->main_block = load_texture(app, "resource/img/main_block.bmp");
    res->additional_block = load_texture(app, "resource/img/additional_block.bmp");
    res->ground = load_texture(app, "resource/img/ground.bmp");
    res->wall = load_texture(app, "resource/img/wall.bmp");
    res->portal = load_texture(app, "resource/img/portal.bmp");
    res->menu_bg_tex = load_texture(app, "resource/img/menu_bg.bmp");
    //Music & sounds
    res->menu_music = Mix_LoadMUS("resource/music/menu.wav");
    res->level_music = Mix_LoadMUS("resource/music/level.wav");
    res->join_sound = Mix_LoadWAV("resource/music/join_sound.wav");
    res->slide_sound = Mix_LoadWAV("resource/music/slide.wav");
    res->select_sound = Mix_LoadWAV("resource/music/select.wav");
    res->portal_sound = Mix_LoadWAV("resource/music/portal_sound.wav");
    //Fonts
    res->monocraft_fnt = TTF_OpenFont("resource/fonts/monocraft/Monocraft.ttf", 24);
    //Text textures
    res->logo_tex = create_text_texture("Wake it up", app, white, res->monocraft_fnt);
    res->start_btn_tex = create_text_texture("New game", app, grey, res->monocraft_fnt);
    res->continue_btn_tex = create_text_texture("Continue", app, grey, res->monocraft_fnt);
    res->exit_btn_tex = create_text_texture("Exit", app, grey, res->monocraft_fnt);
    res->retry_btn_tex = create_text_texture("Retry", app, grey, res->monocraft_fnt);
    res->leave_btn_tex = create_text_texture("Leave", app, grey, res->monocraft_fnt);
    app->res = res;
}

