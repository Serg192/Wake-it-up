#include "../inc/endgame.h"

static inline void shut_down(t_app_global *app) {
    mx_menu_destroy(app);
    mx_app_destroy(app);
    exit(0);
}

static void handle_input(t_app_global *app) {
    t_menu_data *data = app->context;

    SDL_GetMouseState(&(app->mouse_x), &(app->mouse_y));
    while(SDL_PollEvent(&(app->event))) {
        switch(app->event.type) {
            case SDL_QUIT:
                 shut_down(app);
                 break;
            case SDL_MOUSEBUTTONDOWN:
                 if(app->event.button.button == SDL_BUTTON_LEFT) {
                     if(mx_is_intersects(data->start_btn_pos, app->mouse_x, app->mouse_y)) {
                         mx_menu_destroy(app);
                         mx_save_progress(1);
                         mx_play_state_init(app);
                         app->update = mx_play_state_update;
                     }
                     if(mx_is_intersects(data->continue_btn_pos, app->mouse_x, app->mouse_y)) {
                         mx_menu_destroy(app);
                         mx_play_state_init(app);
                         app->update = mx_play_state_update;
                     }
                     if(mx_is_intersects(data->exit_btn_pos, app->mouse_x, app->mouse_y)) {
                         shut_down(app);
                     }
                 }
                 break;
        }
    }
}

void mx_menu_update(t_app_global *app) {
   t_menu_data *data = app->context;
   bool was_selected = false;
   
   SDL_RenderCopy(app->renderer, app->res->menu_bg_tex, NULL, &(data->bg_pos)); 

   SDL_RenderCopy(app->renderer, app->res->logo_tex, NULL, &(data->logo_pos));
   if(mx_is_intersects(data->start_btn_pos, app->mouse_x, app->mouse_y)) {
      SDL_SetTextureColorMod(app->res->start_btn_tex, 0xda, 0xda, 0xda);
      was_selected = true;
   }else
       SDL_SetTextureColorMod(app->res->start_btn_tex, 0xff, 0xff, 0xff);

   if(mx_is_intersects(data->continue_btn_pos, app->mouse_x, app->mouse_y)) {
      SDL_SetTextureColorMod(app->res->continue_btn_tex, 0xda, 0xda, 0xda);
      was_selected = true;
   }else
       SDL_SetTextureColorMod(app->res->continue_btn_tex, 0xff, 0xff, 0xff);
    
   if(mx_is_intersects(data->exit_btn_pos, app->mouse_x, app->mouse_y)) {
      SDL_SetTextureColorMod(app->res->exit_btn_tex, 0xda, 0xda, 0xda);
      was_selected = true;
   }else
       SDL_SetTextureColorMod(app->res->exit_btn_tex, 0xff, 0xff, 0xff);

   SDL_RenderCopy(app->renderer, app->res->start_btn_tex, NULL, &(data->start_btn_pos));
   SDL_RenderCopy(app->renderer, app->res->continue_btn_tex, NULL, &(data->continue_btn_pos));
   SDL_RenderCopy(app->renderer, app->res->exit_btn_tex, NULL, &(data->exit_btn_pos));
   
   SDL_RenderPresent(app->renderer);

   if(was_selected && !data->sound_was_played) {
        data->sound_was_played = true;

        Mix_PlayChannel(-1, app->res->select_sound, 0);
   }
   else if(!was_selected)
        data->sound_was_played = false;

   handle_input(app);
}

