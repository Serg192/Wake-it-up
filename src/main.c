#include "../inc/endgame.h"

int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;

    t_app_global app;
    mx_app_init(&app);
    app.is_running = true;

    t_res res;
    mx_load_res(&app, &res);
    mx_menu_init(&app);
    app.update = mx_menu_update;
   
    while(app.is_running){
        SDL_SetRenderDrawColor(app.renderer, 0x9A, 0x9A, 0x9A, 0xFF);
        SDL_RenderClear(app.renderer);
        app.update(&app);
    }
    mx_app_destroy(&app);
    return 0;
}















	
