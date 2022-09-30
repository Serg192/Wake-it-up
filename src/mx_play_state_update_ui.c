#include "../inc/endgame.h"

static void handle_input(t_app_global *app) {
    t_play_state_data *data = (t_play_state_data*)app->context;
    SDL_GetMouseState(&(app->mouse_x), &(app->mouse_y));
    static bool was_clicked = false;
    if(app->event.type == SDL_MOUSEBUTTONDOWN) {
        if(app->event.button.button == SDL_BUTTON_LEFT) {
            if(!was_clicked) {
                if(mx_is_intersects(data->ret_btn_pos, app->mouse_x, app->mouse_y)) {
                    mx_play_state_destroy(app);
                    mx_play_state_init(app);
                    was_clicked = true;
                 }
                if(mx_is_intersects(data->leave_btn_pos, app->mouse_x, app->mouse_y)) {
                    mx_play_state_destroy(app);
                    mx_menu_init(app);
                    app->update = mx_menu_update;
                    was_clicked = true;
                }
            
            }
        }
    }else
        was_clicked = false;
}

static inline void handle_btn_sound(t_app_global *app, bool was_selected) {
    t_play_state_data *data = (t_play_state_data*)app->context;
    if(was_selected && !data->sound_was_played) {
        data->sound_was_played = true;
        Mix_PlayChannel(-1, app->res->select_sound, 0);
   }
   else if(!was_selected)
        data->sound_was_played = false;
}

static inline void calc_panel_pos(SDL_Rect *res, SDL_Rect *text_pos){
    res->x = text_pos->x - 10;
    res->y = text_pos->y;
    res->w = text_pos->w + 20;
    res->h = text_pos->h + 4;
}

void mx_play_state_update_ui(t_app_global *app) {
    t_play_state_data *data = (t_play_state_data*)app->context;
    bool was_selected = false;    
    SDL_Rect ret_btn_back;
    SDL_Rect leave_btn_back;
    calc_panel_pos(&ret_btn_back, &(data->ret_btn_pos));
    calc_panel_pos(&leave_btn_back, &(data->leave_btn_pos));
    SDL_SetRenderDrawColor(app->renderer, 110, 67, 67, 255);
    SDL_RenderFillRect(app->renderer, &(ret_btn_back));
    SDL_RenderFillRect(app->renderer, &(leave_btn_back));
    
    if(mx_is_intersects(data->ret_btn_pos, app->mouse_x, app->mouse_y)) {
      SDL_SetTextureColorMod(app->res->retry_btn_tex, 0xda, 0xda, 0xda);
      was_selected = true;
   }else
       SDL_SetTextureColorMod(app->res->retry_btn_tex, 0xff, 0xff, 0xff);

   if(mx_is_intersects(data->leave_btn_pos, app->mouse_x, app->mouse_y)) {
      SDL_SetTextureColorMod(app->res->leave_btn_tex, 0xda, 0xda, 0xda);
      was_selected = true;
   }else
       SDL_SetTextureColorMod(app->res->leave_btn_tex, 0xff, 0xff, 0xff);

    SDL_RenderCopy(app->renderer, app->res->retry_btn_tex, NULL, &(data->ret_btn_pos));
    SDL_RenderCopy(app->renderer, app->res->leave_btn_tex, NULL, &(data->leave_btn_pos));

    if(data->alpha >= 0) {
        SDL_SetRenderDrawColor(app->renderer, 0xff, 0xff, 0xff, (int)data->alpha);
        SDL_RenderFillRect(app->renderer, &(data->fade_rec_pos));
        data->alpha -= 0.8f;
   }
   handle_btn_sound(app, was_selected);
   handle_input(app);
}

