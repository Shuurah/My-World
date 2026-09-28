/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** game_render.c
*/

#include "game.h"

bool is_block_exposed(int x, int y, int z, game_t *game)
{
    if (x == game->current_world_size - 1 || y == game->current_world_size - 1
        || z == game->current_world_heigth - 1)
        return true;
    if (get_block_properties(game->world[x + 1][y][z], game)->is_transparent)
        return true;
    if (get_block_properties(game->world[x][y + 1][z], game)->is_transparent)
        return true;
    if (get_block_properties(game->world[x][y][z + 1], game)->is_transparent)
        return true;
    if (z + 1 <= game->layer_displayed)
        return true;
    return false;
}

void rotate_coords(int *x, int *y, int rotation, game_t *game)
{
    int temp;

    switch (rotation) {
        case 1:
            temp = *x;
            *x = *y;
            *y = (game->current_world_size - 1) - temp;
            break;
        case 2:
            *x = (game->current_world_size - 1) - *x;
            *y = (game->current_world_size - 1) - *y;
            break;
        case 3:
            temp = *x;
            *x = (game->current_world_size - 1) - *y;
            *y = temp;
            break;
        default:
            break;
    }
}

static void check_selected(game_t *game, int x, int y, int z)
{
    float tile_width = 16.0f * SCALE * game->camera.camera_zoom;
    float tile_height = 8.0f * SCALE * game->camera.camera_zoom;
    int rot_x = x;
    int rot_y = y;

    rotate_coords(&rot_x, &rot_y, game->camera.rotation, game);
    if (is_block_exposed(rot_x, rot_y, z, game) && game->selected_block.x
        == rot_x && game->selected_block.y == rot_y && game->selected_block.z
        == z){
        sfSprite_setPosition(game->world_builder, (sfVector2f)
            {game->world_builder_x + x * tile_width,
                game->world_builder_y + x * tile_height});
        sfSprite_setTexture(game->world_builder, game->selected_texture, false);
        sfRenderWindow_drawSprite(game->window, game->world_builder, NULL);
    }
}

static void render_display(int y, int z, game_t *game)
{
    float tile_width = 16.0f * SCALE * game->camera.camera_zoom;
    float tile_height = 8.0f * SCALE * game->camera.camera_zoom;
    int rot_x;
    int rot_y;

    for (int x = 0; x < game->current_world_size; x++){
        rot_x = x;
        rot_y = y;
        rotate_coords(&rot_x, &rot_y, game->camera.rotation, game);
        if (game->world[rot_x][rot_y][z] != AIR &&
            is_block_exposed(rot_x, rot_y, z, game)){
            sfSprite_setPosition(game->world_builder, (sfVector2f)
                {game->world_builder_x + x * tile_width,
                    game->world_builder_y + x * tile_height});
            sfSprite_setTexture(game->world_builder, get_block_properties(
                    game->world[rot_x][rot_y][z], game)->texture, false);
            sfRenderWindow_drawSprite(game->window, game->world_builder, NULL);
        }
        check_selected(game, x, y, z);
    }
}

void game_render(game_t *game)
{
    float tile_width = 16.0f * SCALE * game->camera.camera_zoom;
    float tile_height = 8.0f * SCALE * game->camera.camera_zoom;
    float layer_offset = 15.0f * SCALE * game->camera.camera_zoom;

    game->world_builder_x = game->camera.camera_x;
    game->world_builder_y = game->camera.camera_y;
    sfSprite_setScale(game->world_builder, (sfVector2f)
        {SCALE * game->camera.camera_zoom, SCALE * game->camera.camera_zoom});
    for (int z = 0; z < game->layer_displayed; z++){
        for (int y = 0; y < game->current_world_size; y++){
            render_display(y, z, game);
            game->world_builder_x -= tile_width;
            game->world_builder_y += tile_height;
        }
        game->world_builder_x += tile_width * game->current_world_size;
        game->world_builder_y -= tile_height * game->current_world_size
            + layer_offset;
    }
}
