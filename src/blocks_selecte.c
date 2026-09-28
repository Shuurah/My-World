/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** block_selecte.c
*/

#include "game.h"

void select_block_grass(game_t *game)
{
    game->selected_block.id_replace = GRASS;
    sfSprite_setTexture(game->selected_block.sprite,
        get_block_properties(GRASS, game)->texture, sfFalse);
}

void select_block_stone(game_t *game)
{
    game->selected_block.id_replace = STONE;
    sfSprite_setTexture(game->selected_block.sprite,
        get_block_properties(STONE, game)->texture, sfFalse);
}

void select_block_tile(game_t *game)
{
    game->selected_block.id_replace = TILE;
    sfSprite_setTexture(game->selected_block.sprite,
        get_block_properties(TILE, game)->texture, sfFalse);
}

void select_block_water(game_t *game)
{
    game->selected_block.id_replace = WATER;
    sfSprite_setTexture(game->selected_block.sprite,
        get_block_properties(WATER, game)->texture, sfFalse);
}
