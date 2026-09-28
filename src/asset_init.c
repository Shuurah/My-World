/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** asset_init.c
*/

#include "game.h"

void print_info_bug(void)
{
    printf("\n<==========================[IMPORTANT]=======================>");
    printf("\nINFORMATION : there is a bug with the mouse (a little offset)\n");
    printf("the more your mouse is in the bottom of the screen, ");
    printf("the more the offset will be present\ntry to click on the bottoms");
    printf(" button/text input with an upper offset\nsorry :(\n");
    printf("<==========================[IMPORTANT]=======================>\n");
}

void create_selection(game_t *game)
{
    game->ui.buttons[20] = *create_button(
        &(sfFloatRect){game->window_x - 175,
            game->window_y - 750, 170, 40},
        "current block", NULL, game);
    game->ui.buttons[21] = *create_button(
        &(sfFloatRect){game->window_x - 110,
            game->window_y - 700, game->window_x / 22, game->window_x / 22},
        "", NULL, game);
    sfSprite_setPosition(game->selected_block.sprite, (sfVector2f)
        {game->window_x - 100, game->window_y - 690});
    sfSprite_setScale(game->selected_block.sprite, (sfVector2f){2, 2});
    sfSprite_setTexture(game->selected_block.sprite, get_block_properties(
            game->selected_block.id_replace, game)->texture, sfFalse);
}

void init_button_zoom(game_t *game)
{
    game->ui.buttons[22] = *create_button(
        &(sfFloatRect){game->window_x - 120,
            10, 105, 40},
        "zoom in", zoom_in, game);
    game->ui.buttons[23] = *create_button(
        &(sfFloatRect){game->window_x - 365,
            10, 105, 40},
        "zoom out", zoom_out, game);
}

static void init_ui_save_load(game_t *game)
{
    game->ui.buttons[24] = *create_button(
        &(sfFloatRect){350,
            game->window_y - 50, 105, 40},
        "save", save_world, game);
    game->ui.buttons[25] = *create_button(
        &(sfFloatRect){475,
            game->window_y - 50, 105, 40},
        "load", load_world, game);
}

static void init_ui_other_button_extend(game_t *game)
{
    game->ui.buttons[16] = *create_button(
        &(sfFloatRect){game->window_x - 120,
            game->window_y - 450, 105, 40},
        "GRASS", select_block_grass, game);
    game->ui.buttons[17] = *create_button(
        &(sfFloatRect){game->window_x - 120,
            game->window_y - 400, 105, 40},
        "STONE", select_block_stone, game);
    game->ui.buttons[18] = *create_button(
        &(sfFloatRect){game->window_x - 120,
            game->window_y - 350, 105, 40},
        "TILE", select_block_tile, game);
    game->ui.buttons[19] = *create_button(
        &(sfFloatRect){game->window_x - 120,
            game->window_y - 300, 105, 40},
        "WATER", select_block_water, game);
    init_button_zoom(game);
    init_ui_save_load(game);
    create_selection(game);
}

static void init_ui_other_button_block(game_t *game)
{
    game->ui.buttons[12] = *create_button(
        &(sfFloatRect){game->window_x - 235,
            game->window_y - 200, 105, 40},
        "Place", place_block, game);
    game->ui.buttons[13] = *create_button(
        &(sfFloatRect){game->window_x - 120,
            game->window_y - 600, 105, 40},
        "BEDROCK", select_block_bedrock, game);
    game->ui.buttons[14] = *create_button(
        &(sfFloatRect){game->window_x - 120,
            game->window_y - 550, 105, 40},
        "DIRT", select_block_dirt, game);
    game->ui.buttons[15] = *create_button(
        &(sfFloatRect){game->window_x - 120,
            game->window_y - 500, 105, 40},
        "GLASS", select_block_glass, game);
    init_ui_other_button_extend(game);
}

static void init_ui_other_button(game_t *game)
{
    game->ui.buttons[8] = *create_button(
        &(sfFloatRect){game->window_x - 235,
            game->window_y - 100, 105, 40},
        "select Y-", selected_y_negative, game);
    game->ui.buttons[9] = *create_button(
        &(sfFloatRect){game->window_x - 120,
            game->window_y - 150, 105, 40},
        "select Z+", selected_z_positive, game);
    game->ui.buttons[10] = *create_button(
        &(sfFloatRect){game->window_x - 235,
            game->window_y - 150, 105, 40},
        "select Z-", selected_z_negative, game);
    game->ui.buttons[11] = *create_button(
        &(sfFloatRect){game->window_x - 120,
            game->window_y - 200, 105, 40},
        "Destroy", destroy_block, game);
    init_ui_other_button_block(game);
}

static void init_ui_other(game_t *game)
{
    game->ui.buttons[4] = *create_button(
        &(sfFloatRect){game->window_x - 365,
            60, 105, 40},
        "<- Rotate", turn_left, game);
    game->ui.buttons[5] = *create_button(
        &(sfFloatRect){game->window_x - 120,
            game->window_y - 50, 105, 40},
        "select X+", selected_x_positive, game);
    game->ui.buttons[6] = *create_button(
        &(sfFloatRect){game->window_x - 235,
            game->window_y - 50, 105, 40},
        "select X-", selected_x_negative, game);
    game->ui.buttons[7] = *create_button(
        &(sfFloatRect){game->window_x - 120,
            game->window_y - 100, 105, 40},
        "select Y+", selected_y_positive, game);
    init_ui_other_button(game);
}

void escape(game_t *game)
{
    sfRenderWindow_close(game->window);
}

void init_ui(game_t *game)
{
    game->ui.font = sfFont_createFromFile("font/Blue Winter.ttf");
    if (!game->ui.font)
        fprintf(stderr, "Error: Could not load font\n");
    game->ui.button_count = TOTAL_BUTTON;
    game->ui.buttons = malloc(sizeof(button_t) * game->ui.button_count);
    game->ui.buttons[0] = *create_button(
        &(sfFloatRect){20, 20, 150, 40},
        "Escape Game", open_main_menu, game);
    game->ui.buttons[1] = *create_button(
        &(sfFloatRect){game->window_x - 250,
            10, 120, 40}, "Layer Up", go_up_layer, game);
    game->ui.buttons[2] = *create_button(
        &(sfFloatRect){game->window_x - 250,
            60, 120, 40}, "Layer Down", go_down_layer, game);
    game->ui.buttons[3] = *create_button(
        &(sfFloatRect){game->window_x - 120,
            60, 105, 40}, "Rotate ->", turn_right, game);
    init_ui_other(game);
}
