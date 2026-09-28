/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** program_init.c
*/

#include "game.h"


static int get_surface_height(int wx, int wy, game_t *game)
{
    float fwx = (float)wx;
    float fwy = (float)wy;
    sfVector2f coord = (sfVector2f){fwx, fwy};
    float n = perlin2d(&coord, TERRAIN_FREQ, TERRAIN_DEPTH, game);
    int h = TERRAIN_MIN + (int)(n * (float)TERRAIN_RANGE);

    if (h < 3)
        h = 3;
    if (h >= WORLD_HEIGHT - 1)
        h = WORLD_HEIGHT - 2;
    return h;
}

static void fill_water(game_t *game, int x, int y)
{
    for (int i = TERRAIN_MIN; i <= SEA_LEVEL; i++){
        if (game->world[x][y][i] == AIR)
            game->world[x][y][i] = WATER;
    }
}

static void generate_layer(game_t *game, int surface, int x, int y)
{
    for (int z = 2; z < surface - 3; z++)
        game->world[x][y][z] = STONE;
    for (int z = surface - 3; z < surface; z++) {
        if (z >= 3)
            game->world[x][y][z] = DIRT;
    }
    if (surface < SEA_LEVEL)
        fill_water(game, x, y);
    else
        game->world[x][y][surface] = GRASS;
}

void fill_air(game_t *game, int x, int y)
{
    for (int z = 0; z < game->current_world_heigth; z++)
        game->world[x][y][z] = AIR;
}

void check_selected_coord(game_t *game, int x, int y, int surface)
{
    if (x == game->current_world_size / 2
        && (y == game->current_world_size / 2)){
        game->selected_block.x = x;
        game->selected_block.y = y;
        game->selected_block.z = surface + 1;
    }
}

void create_world(game_t *game)
{
    int surface;

    for (int x = 0; x < game->current_world_size; x++){
        for (int y = 0; y < game->current_world_size; y++)
            fill_air(game, x, y);
    }
    for (int x = 0; x < game->current_world_size; x++) {
        for (int y = 0; y < game->current_world_size; y++) {
            surface = get_surface_height(x, y, game);
            check_selected_coord(game, x, y, surface);
            game->world[x][y][0] = BEDROCK;
            game->world[x][y][1] = (rand() % 100 < 50) ? BEDROCK : STONE;
            generate_layer(game, surface, x, y);
        }
    }
}
