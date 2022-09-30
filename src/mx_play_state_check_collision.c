#include "../inc/endgame.h"

bool mx_check_collision_upperY(t_app_global *app) {
	t_play_state_data *data = app->context;
	int x;
	int y;
	for (int i = 0; i < data->level->entity_count; i++) {
        if (data->level->entities[i].activated) {
        	x = data->level->entities[i].x_pos;
			y = data->level->entities[i].y_pos;
        	
        	if (data->level->tiles[y - 1][x] == 1) {
            	return false;
            }
        }
	}
	return true;
}

bool mx_check_collision_bottomY(t_app_global *app) {
	t_play_state_data *data = app->context;
	int x;
	int y;
	for (int i = 0; i < data->level->entity_count; i++) {
        if (data->level->entities[i].activated) {
        	x = data->level->entities[i].x_pos;
			y = data->level->entities[i].y_pos;
        	
        	if (data->level->tiles[y + 1][x] == 1) {
            	return false;
            }
        }
	}
	return true;
}

bool mx_check_collision_rightX(t_app_global *app) {	
	t_play_state_data *data = app->context;
	int x;
	int y;
	for (int i = 0; i < data->level->entity_count; i++) {
        if (data->level->entities[i].activated) {
        	x = data->level->entities[i].x_pos;
			y = data->level->entities[i].y_pos;
        	
        	if (data->level->tiles[y][x + 1] == 1) {
            	return false;
            }
        }
	}
	return true;
}

bool mx_check_collision_leftX(t_app_global *app) {
	t_play_state_data *data = app->context;
	int x;
	int y;
	for (int i = 0; i < data->level->entity_count; i++) {
        if (data->level->entities[i].activated) {
        	x = data->level->entities[i].x_pos;
			y = data->level->entities[i].y_pos;
        	
        	if (data->level->tiles[y][x - 1] == 1) {
            	return false;
            }
        }
	}
	return true;
}


