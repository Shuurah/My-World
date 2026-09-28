/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** window.c
*/

#include "game.h"

static void rotation_handler(game_t *game)
{
    float elapsed = sfTime_asSeconds(sfClock_getElapsedTime(game->input_delay));

    if (elapsed > INPUT_DELAY) {
        if (sfKeyboard_isKeyPressed(sfKeyQ)) {
            turn_left(game);
            sfClock_restart(game->input_delay);
        }
        if (sfKeyboard_isKeyPressed(sfKeyD)) {
            turn_right(game);
            sfClock_restart(game->input_delay);
        }
    }
}

void zoom_in(game_t *game)
{
    game->camera.camera_zoom += 0.01f;
    if (game->camera.camera_zoom > MIN_CAMERA_ZOOM)
        game->camera.camera_zoom = MIN_CAMERA_ZOOM;
}

void zoom_out(game_t *game)
{
    game->camera.camera_zoom -= 0.01f;
    if (game->camera.camera_zoom < MAX_CAMERA_ZOOM)
        game->camera.camera_zoom = MAX_CAMERA_ZOOM;
}

static void camera_handler(game_t *game)
{
    if (sfKeyboard_isKeyPressed(sfKeyDown))
        game->camera.camera_y -= game->camera.camera_speed;
    if (sfKeyboard_isKeyPressed(sfKeyUp))
        game->camera.camera_y += game->camera.camera_speed;
    if (sfKeyboard_isKeyPressed(sfKeyRight))
        game->camera.camera_x -= game->camera.camera_speed;
    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        game->camera.camera_x += game->camera.camera_speed;
    if (sfKeyboard_isKeyPressed(sfKeyA)){
        game->camera.camera_zoom -= 0.01f;
        if (game->camera.camera_zoom < MAX_CAMERA_ZOOM)
            game->camera.camera_zoom = MAX_CAMERA_ZOOM;
    }
    if (sfKeyboard_isKeyPressed(sfKeyE)){
        game->camera.camera_zoom += 0.01f;
        if (game->camera.camera_zoom > MIN_CAMERA_ZOOM)
            game->camera.camera_zoom = MIN_CAMERA_ZOOM;
    }
}

static void layer_handler(game_t *game)
{
    float elapsed = sfTime_asSeconds(sfClock_getElapsedTime(game->input_delay));

    if (elapsed < INPUT_DELAY)
        return;
    if (sfKeyboard_isKeyPressed(sfKeyS))
        go_down_layer(game);
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        go_up_layer(game);
    sfClock_restart(game->input_delay);
}

void handle_keys(game_t *game)
{
    if (sfKeyboard_isKeyPressed(sfKeyLShift))
        game->camera.camera_speed = CAMERA_SPEED * 2.0f;
    else
        game->camera.camera_speed = CAMERA_SPEED;
    camera_handler(game);
    rotation_handler(game);
    layer_handler(game);
}
