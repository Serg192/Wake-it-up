#include "../inc/endgame.h"

SDL_Texture *mx_get_texture(t_res *res, int tex_id){
    switch(tex_id){
        case GROUND_TEX:
            return res->ground;
        case WALL_TEX:
            return res->wall;
        case MOVE_HERE_TEX:
        	return res->move_here;
        case PORTAL_TEX:
        	return res->portal;
        default:
            return NULL;
   }
}

