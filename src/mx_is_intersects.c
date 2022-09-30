#include "../inc/endgame.h"

bool mx_is_intersects(SDL_Rect rect, int x, int y) {
    (void)y;
    if(x >= rect.x && x <= rect.x + rect.w &&
       y >= rect.y && y <= rect.y + rect.h)
        return true;
    return false;
}


