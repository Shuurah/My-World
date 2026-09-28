/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** block_handler.c
*/

#include "game.h"

void place_block(game_t *game)
{
    game->world[game->selected_block.x][game->selected_block.y]
    [game->selected_block.z] = game->selected_block.id_replace;
}

void destroy_block(game_t *game)
{
    game->world[game->selected_block.x][game->selected_block.y]
    [game->selected_block.z] = AIR;
}

void select_block_bedrock(game_t *game)
{
    game->selected_block.id_replace = BEDROCK;
    sfSprite_setTexture(game->selected_block.sprite,
        get_block_properties(BEDROCK, game)->texture, sfFalse);
}

void select_block_dirt(game_t *game)
{
    game->selected_block.id_replace = DIRT;
    sfSprite_setTexture(game->selected_block.sprite,
        get_block_properties(DIRT, game)->texture, sfFalse);
}

void select_block_glass(game_t *game)
{
    game->selected_block.id_replace = GLASS;
    sfSprite_setTexture(game->selected_block.sprite,
        get_block_properties(GLASS, game)->texture, sfFalse);
}
