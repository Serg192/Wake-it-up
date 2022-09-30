#include "../inc/endgame.h"

static void handle_input(t_app_global *app) {
	t_play_state_data *data = app->context;
    while (SDL_PollEvent(&(app->event))) {
    	switch (app->event.type) {
    		case SDL_QUIT:
				app->is_running = false;
                mx_play_state_destroy(app);
				break;
			case SDL_KEYUP:
				 switch (app->event.key.keysym.sym) {
				 	case SDLK_UP:
				 		if (mx_check_collision_upperY(app)) {
				 			for (int i = 0; i < data->level->entity_count; i++) {
				 				if (data->level->entities[i].activated) {
				 					data->level->entities[i].y_pos -= 1;
				 					app->context = data;
				 					Mix_PlayChannel(-1, app->res->slide_sound, 0);
				 				}
				 			}
						}
				 		break;
				 	case SDLK_DOWN:
				 		if (mx_check_collision_bottomY(app)) {
				 			for (int i = 0; i < data->level->entity_count; i++) {
				 				if (data->level->entities[i].activated) {
				 					data->level->entities[i].y_pos += 1;
				 					app->context = data;
				 					Mix_PlayChannel(-1, app->res->slide_sound, 0);
				 				}
				 			}
						}
				 		break;
				 	case SDLK_RIGHT:
				 		if (mx_check_collision_rightX(app)) {
				 			for (int i = 0; i < data->level->entity_count; i++) {
				 				if (data->level->entities[i].activated) {
				 					data->level->entities[i].x_pos += 1;
				 					app->context = data;
				 					Mix_PlayChannel(-1, app->res->slide_sound, 0);
				 				}		
							}
						}
				 		break;
				 	case SDLK_LEFT:
				 		if (mx_check_collision_leftX(app)) {
				 			for (int i = 0; i < data->level->entity_count; i++) {
				 				if (data->level->entities[i].activated) {
				 					data->level->entities[i].x_pos -= 1;
				 					app->context = data;
				 					Mix_PlayChannel(-1, app->res->slide_sound, 0);
				 				}
				 			}
				 		}
				 		break;
				 }
				break;	
    	}
    }
}

static void wake_up(t_app_global *app) {
	//WAKE UP!
	t_play_state_data *data = app->context;
    for (int i = 0; i < data->level->entity_count; i++) {
		if (data->level->entities[i].activated) {
			for (int j = 0; j < data->level->entity_count; j++) {
				if (data->level->entities[j].activated == false) {
					if (((data->level->entities[i].x_pos == data->level->entities[j].x_pos) && (data->level->entities[i].y_pos - data->level->entities[j].y_pos == 1))
						|| ((data->level->entities[i].x_pos == data->level->entities[j].x_pos) && (data->level->entities[i].y_pos - data->level->entities[j].y_pos == -1))
						|| ((data->level->entities[i].y_pos == data->level->entities[j].y_pos) && (data->level->entities[i].x_pos - data->level->entities[j].x_pos == 1))
						|| ((data->level->entities[i].y_pos == data->level->entities[j].y_pos) && (data->level->entities[i].x_pos - data->level->entities[j].x_pos == -1))) {
						data->level->entities[j].activated = true;
						Mix_PlayChannel(1, app->res->join_sound, 0);
					}
				}
			}
		}
	}
}

static bool check_level_complete(t_app_global *app) {
	t_play_state_data *data = app->context;
	int x;
	int y;
	for (int i = 0; i < data->level->entity_count; i++) {
        if (data->level->entities[i].activated) {
        	x = data->level->entities[i].x_pos;
			y = data->level->entities[i].y_pos;
        	
        	if (data->level->tiles[y][x] != 2) {
            	return false;
            }
        }
        else
        	return false;
	}
	return true;
}

static void portal_entrance(t_app_global *app) {
	t_play_state_data *data = app->context;
	int x;
	int y;
	for (int i = 0; i < data->level->entity_count; i++) {
        if (data->level->entities[i].activated) {
        	x = data->level->entities[i].x_pos;
			y = data->level->entities[i].y_pos;
        	
        	if (data->level->tiles[y][x] == 3) {
        		Mix_PlayChannel(1, app->res->portal_sound, 0);
            	for (int j = 0; j < data->level->entity_count; j++) {
            		data->level->entities[i].x_pos = 100;
            		data->level->entities[i].y_pos = 100;
            		data->level->entities[i].activated = false;
            	}
            }
        }
	}
}

void mx_play_state_update(t_app_global *app) {
    t_play_state_data *data = app->context;
    portal_entrance(app);
    wake_up(app);
    
    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        for (int j = 0; j < LEVEL_WIDTH; j++) {
            data->tile_pos.x = j * TILE_WIDTH;
            data->tile_pos.y = i * TILE_HEIGHT;
            SDL_Texture * texture = mx_get_texture(app->res, data->level->tiles[i][j]);
            SDL_RenderCopy(app->renderer, texture, NULL, &(data->tile_pos));
        }
    }
    
    for (int i = 0; i < data->level->entity_count; i++) {
    	data->tile_pos.x = TILE_WIDTH * data->level->entities[i].x_pos;
    	data->tile_pos.y = TILE_HEIGHT * data->level->entities[i].y_pos;
		if (data->level->entities[i].activated) {
			SDL_RenderCopy(app->renderer, app->res->main_block, NULL, &(data->tile_pos));
		}
		else {
			SDL_RenderCopy(app->renderer, app->res->additional_block, NULL, &(data->tile_pos));
		}
    }
    
    bool game_over = false;
    if (check_level_complete(app)) {
        if(app->current_level + 1 <= LEVEL_MAX){
            app->current_level += 1;
            mx_save_progress(app->current_level);
        } else{
            mx_play_state_destroy(app);
            mx_menu_init(app);
            app->update = mx_menu_update;
            game_over = true;
        }
        if(!game_over){
            mx_play_state_destroy(app);
            mx_play_state_init(app);
        }
    }
    if(!game_over){
        handle_input(app);
        mx_play_state_update_ui(app);
        SDL_RenderPresent(app->renderer);
    }
}


