#!/bin/bash
cd ..
clang -std=c11 -Wall -Werror -Wextra -Wpedantic -I/usr/include/SDL2  -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf src/*.c -o endgame


