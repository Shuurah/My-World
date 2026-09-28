/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** layer.c
*/

#include "game.h"

void go_down_layer(game_t *game)
{
    game->layer_displayed -= 1;
    if (game->layer_displayed < 0)
        game->layer_displayed = 0;
}

void go_up_layer(game_t *game)
{
    game->layer_displayed += 1;
    if (game->layer_displayed > game->current_world_heigth)
        game->layer_displayed = game->current_world_heigth;
}

void turn_right(game_t *game)
{
    game->camera.rotation = (game->camera.rotation + 1) % 4;
}

void turn_left(game_t *game)
{
    game->camera.rotation = (game->camera.rotation - 1 + 4) % 4;
}

void selected_z_positive(game_t *game)
{
    game->selected_block.z += 1;
    if (game->selected_block.z > game->current_world_heigth - 1)
        game->selected_block.z = game->current_world_heigth - 1;
}
