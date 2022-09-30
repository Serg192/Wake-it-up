#ifndef ENDGAME_H
#define ENDGAME_H
/*
 *map is 20 x 12
 */
#define WIN_WIDTH  1280
#define WIN_HEIGHT 768

#define LEVEL_WIDTH 20
#define LEVEL_HEIGHT 12
#define TILE_WIDTH 64
#define TILE_HEIGHT 64

#define LEVEL_MAX 10

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_entity {
    int x_pos;
    int y_pos;
    bool activated;
}              t_entity;

typedef struct s_level {
    int **tiles;
    int entity_count;
    t_entity *entities;
}              t_level;

typedef struct s_res {
    //Textures
    SDL_Texture *move_here;
    SDL_Texture *main_block;
    SDL_Texture *additional_block;
    SDL_Texture *ground;
    SDL_Texture *wall;
    SDL_Texture *portal;
    //Menu textures
    SDL_Texture *logo_tex;
    SDL_Texture *start_btn_tex;
    SDL_Texture *continue_btn_tex;
    SDL_Texture *exit_btn_tex;
    SDL_Texture *menu_bg_tex;
    SDL_Texture *retry_btn_tex;
    SDL_Texture *leave_btn_tex;

    //
    //Music and sounds
    Mix_Music *menu_music;
    Mix_Music *level_music;
    Mix_Chunk *join_sound;
    Mix_Chunk *slide_sound;
    Mix_Chunk *select_sound;
    Mix_Chunk *portal_sound;
    //
    //Fonts
    TTF_Font *monocraft_fnt;
}              t_res;

typedef struct s_app_global {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    void(*update)(struct s_app_global *app);
    void *context;
    t_res *res;
    bool is_running;
    int mouse_x;
    int mouse_y;
    int current_level;
}              t_app_global;

typedef struct s_menu_data {
    SDL_Rect bg_pos;
    SDL_Rect logo_pos;
    SDL_Rect start_btn_pos;
    SDL_Rect continue_btn_pos;
    SDL_Rect exit_btn_pos;
    bool sound_was_played;
}              t_menu_data;

typedef struct s_play_state_data {
    t_level *level;
    SDL_Rect tile_pos;
    SDL_Rect ret_btn_pos;
    SDL_Rect leave_btn_pos;
    SDL_Rect ui_panel;
    float alpha;
    SDL_Rect fade_rec_pos;
    bool sound_was_played;
}              t_play_state_data;

enum e_tex_id {
    GROUND_TEX,
    WALL_TEX,
    MOVE_HERE_TEX,
    PORTAL_TEX,
};

void mx_menu_init(t_app_global *app);

void mx_menu_update(t_app_global *app);

void mx_menu_destroy(t_app_global *app);

void mx_play_state_init(t_app_global *app);

void mx_play_state_update(t_app_global *app);

void mx_play_state_destroy(t_app_global *app);

bool mx_check_collision_upperY(t_app_global *app);

bool mx_check_collision_bottomY(t_app_global *app);

bool mx_check_collision_rightX(t_app_global *app);

bool mx_check_collision_leftX(t_app_global *app);

void mx_play_state_update_ui(t_app_global *app);
//initialize SDL
void mx_app_init(t_app_global * global);

void mx_app_destroy(t_app_global *global);

void mx_printerr(const char *err);

void mx_load_res(t_app_global *app, t_res *res);

t_level *mx_parse_level(const char *level_path);

SDL_Texture *mx_get_texture(t_res *res, int tex_id);

t_level* mx_get_saved_level(t_app_global *app);

void mx_save_progress(int level_n);

bool mx_is_intersects(SDL_Rect rect, int x, int y);

#endif

