/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** program_init.c
*/

#include "game.h"


int write_err(char *message, int return_value)
{
    int error_len = strlen(message);

    write(2, message, error_len);
    return return_value;
}

static void exit_before_start(int code, char *message, game_t *game)
{
    write_err(message, 84);
    free(game);
    exit(code);
}

void quit_game(game_t *game)
{
    sfRenderWindow_close(game->window);
}

void parser(int argc, char *argv[], char **env, game_t *game)
{
    if (argc > 2)
        exit_before_start(84, "invalid arguments\n", game);
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        display_help();
        exit_before_start(0, "", game);
    }
    if (argc == 2)
        exit_before_start(84, "invalid arguments\n", game);
    if (!has_display(env))
        exit_before_start(84, "no graphical interface\n", game);
    return;
}

static void init_other(game_t *game)
{
    game->layer_displayed = game->current_world_heigth;
    game->selected_texture =
        sfTexture_createFromFile("texture/selected.png", NULL);
    game->selected_block.x = WORLD_SIZE / 2;
    game->selected_block.y = WORLD_SIZE / 2;
    game->selected_block.z = 6;
    srand(time(NULL));
    game->seed = rand() % 10000;
    setup_file_input(game);
    print_info_bug();
    open_main_menu(game);
}

void init_all(game_t *game)
{
    game->window = create_window(SCREEN_LEN, SCREEN_HEIGHT);
    game->window_x = sfRenderWindow_getSize(game->window).x;
    game->window_y = sfRenderWindow_getSize(game->window).y;
    game->selected_block.sprite = sfSprite_create();
    game->selected_block.id_replace = TILE;
    init_block_registry(game);
    init_ui(game);
    init_menu_buttons(game);
    game->world_builder = sfSprite_create();
    sfSprite_setScale(game->world_builder, (sfVector2f){SCALE, SCALE});
    sfSprite_setTexture(game->world_builder,
        game->blocks_registry.blocks[TILE].texture, sfTrue);
    game->camera.camera_x = 800;
    game->camera.camera_y = 300;
    game->camera.camera_zoom = 0.5f;
    game->camera.rotation = 0;
    game->input_delay = sfClock_create();
    game->current_world_heigth = WORLD_HEIGHT;
    game->current_world_size = WORLD_SIZE;
    init_other(game);
}
