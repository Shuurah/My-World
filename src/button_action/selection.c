/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** layer.c
*/

#include "game.h"

void selected_x_negative(game_t *game)
{
    game->selected_block.x -= 1;
    if (game->selected_block.x < 0)
        game->selected_block.x = 0;
}

void selected_x_positive(game_t *game)
{
    game->selected_block.x += 1;
    if (game->selected_block.x > game->current_world_size - 1)
        game->selected_block.x = game->current_world_size - 1;
}

void selected_y_negative(game_t *game)
{
    game->selected_block.y -= 1;
    if (game->selected_block.y < 0)
        game->selected_block.y = 0;
}

void selected_y_positive(game_t *game)
{
    game->selected_block.y += 1;
    if (game->selected_block.y > game->current_world_size - 1)
        game->selected_block.y = game->current_world_size - 1;
}

//the positive is in button_action/layer.c
void selected_z_negative(game_t *game)
{
    game->selected_block.z -= 1;
    if (game->selected_block.z < 0)
        game->selected_block.z = 0;
}
