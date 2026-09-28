/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** main_menu.c
*/

#include "game.h"

static void hide_menu_buttons(game_t *game)
{
    game->ui.buttons[MENU_BTN_START].is_visible = false;
    game->ui.buttons[MENU_BTN_SETTINGS].is_visible = false;
    game->ui.buttons[MENU_BTN_QUIT].is_visible = false;
    game->ui.buttons[MENU_BTN_SMALL].is_visible = false;
    game->ui.buttons[MENU_BTN_MEDIUM].is_visible = false;
    game->ui.buttons[MENU_BTN_LARGE].is_visible = false;
    game->ui.buttons[MENU_BTN_BACK].is_visible = false;
}

void start_game(game_t *game)
{
    hide_menu_buttons(game);
    create_world(game);
    for (int i = 0; i < 26; i++)
        game->ui.buttons[i].is_visible = true;
    game->is_ingame = true;
}

static void open_settings(game_t *game)
{
    game->ui.buttons[MENU_BTN_START].is_visible = false;
    game->ui.buttons[MENU_BTN_SETTINGS].is_visible = false;
    game->ui.buttons[MENU_BTN_QUIT].is_visible = false;
    game->ui.buttons[MENU_BTN_SMALL].is_visible = true;
    game->ui.buttons[MENU_BTN_MEDIUM].is_visible = true;
    game->ui.buttons[MENU_BTN_LARGE].is_visible = true;
    game->ui.buttons[MENU_BTN_BACK].is_visible = true;
}

static void set_small_world(game_t *game)
{
    game->current_world_size = 16;
    open_main_menu(game);
}

static void set_medium_world(game_t *game)
{
    game->current_world_size = 32;
    open_main_menu(game);
}

static void set_large_world(game_t *game)
{
    game->current_world_size = 64;
    open_main_menu(game);
}

void init_settings_buttons(game_t *game)
{
    sfFloatRect rect_small = {710, 480, 150, 55};
    sfFloatRect rect_medium = {885, 480, 150, 55};
    sfFloatRect rect_large = {1060, 480, 150, 55};
    sfFloatRect rect_back = {760, 560, 400, 55};

    game->ui.buttons[MENU_BTN_SMALL] = *create_button(&rect_small,
        "Small (16)", set_small_world, game);
    game->ui.buttons[MENU_BTN_MEDIUM] = *create_button(&rect_medium,
        "Medium (32)", set_medium_world, game);
    game->ui.buttons[MENU_BTN_LARGE] = *create_button(&rect_large,
        "Large (64)", set_large_world, game);
    game->ui.buttons[MENU_BTN_BACK] = *create_button(&rect_back,
        "Back", open_main_menu, game);
}

void init_bg(game_t *game)
{
    sfVector2f scale;

    game->menu_bg_texture =
        sfTexture_createFromFile("texture/menu.png", NULL);
    game->menu_bg = sfSprite_create();
    if (!game->menu_bg_texture || !game->menu_bg)
        return;
    sfSprite_setTexture(game->menu_bg, game->menu_bg_texture, sfTrue);
    scale.x = (float)game->window_x
        / sfTexture_getSize(game->menu_bg_texture).x;
    scale.y = (float)game->window_y
        / sfTexture_getSize(game->menu_bg_texture).y;
    sfSprite_setScale(game->menu_bg, scale);
}

void open_main_menu(game_t *game)
{
    game->is_ingame = false;
    game->ui.buttons[MENU_BTN_START].is_visible = true;
    game->ui.buttons[MENU_BTN_SETTINGS].is_visible = true;
    game->ui.buttons[MENU_BTN_QUIT].is_visible = true;
    game->ui.buttons[MENU_BTN_SMALL].is_visible = false;
    game->ui.buttons[MENU_BTN_MEDIUM].is_visible = false;
    game->ui.buttons[MENU_BTN_LARGE].is_visible = false;
    game->ui.buttons[MENU_BTN_BACK].is_visible = false;
    for (int i = 0; i < 26; i++)
        game->ui.buttons[i].is_visible = false;
}

void init_menu_buttons(game_t *game)
{
    sfFloatRect rect_start = {760, 400, 400, 55};
    sfFloatRect rect_settings = {760, 480, 400, 55};
    sfFloatRect rect_quit = {760, 560, 400, 55};
    button_t *btn = NULL;

    btn = create_button(&rect_start, "Start", start_game, game);
    if (btn)
        game->ui.buttons[MENU_BTN_START] = *btn;
    btn = create_button(&rect_settings, "Settings", open_settings, game);
    if (btn)
        game->ui.buttons[MENU_BTN_SETTINGS] = *btn;
    btn = create_button(&rect_quit, "Quit", quit_game, game);
    if (btn)
        game->ui.buttons[MENU_BTN_QUIT] = *btn;
    init_settings_buttons(game);
    init_bg(game);
    setup_file_input(game);
    open_main_menu(game);
}
