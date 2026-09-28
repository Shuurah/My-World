/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** block_registry.c
*/

#include "game.h"

static void block_init_full(game_t *game)
{
    register_block(&(block_properties_t){.id = STONE,
            .is_transparent = false, .texture = sfTexture_createFromFile
                ("texture/stone.png", NULL)}, game);
    register_block(&(block_properties_t){.id = GLASS,
            .is_transparent = true, .texture = sfTexture_createFromFile
                ("texture/glass.png", NULL)}, game);
    register_block(&(block_properties_t){.id = WATER,
            .is_transparent = false, .texture = sfTexture_createFromFile
                ("texture/water.png", NULL)}, game);
}

void init_block_registry(game_t *game)
{
    game->blocks_registry.registered_count = 0;
    memset(&game->blocks_registry.blocks, 0,
        sizeof(game->blocks_registry.blocks));
    register_block(&(block_properties_t){.id = AIR, .is_transparent = true,
            .texture = NULL}, game);
    register_block(&(block_properties_t){.id = TILE, .is_transparent = false,
            .texture = sfTexture_createFromFile("texture/tile_basic.png", NULL)
        }, game);
    register_block(&(block_properties_t){.id = BEDROCK,
            .is_transparent = false, .texture = sfTexture_createFromFile
                ("texture/bedrock.png", NULL)}, game);
    register_block(&(block_properties_t){.id = DIRT,
            .is_transparent = false, .texture = sfTexture_createFromFile
                ("texture/dirt.png", NULL)}, game);
    register_block(&(block_properties_t){.id = GRASS,
            .is_transparent = false, .texture = sfTexture_createFromFile
                ("texture/grass.png", NULL)}, game);
    block_init_full(game);
}

void register_block(block_properties_t *properties, game_t *game)
{
    if (properties->id >= MAX_BLOCK_TYPES) {
        fprintf(stderr, "Error: Block ID %d exceeds MAX_BLOCK_TYPES\n",
            properties->id);
        return;
    }
    game->blocks_registry.blocks[properties->id] = *properties;
    game->blocks_registry.registered_count++;
}

block_properties_t *get_block_properties(int block_id, game_t *game)
{
    if (block_id < 0 || block_id >= MAX_BLOCK_TYPES)
        return &game->blocks_registry.blocks[AIR];
    return &game->blocks_registry.blocks[block_id];
}
