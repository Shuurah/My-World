/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** window.c
*/

#include "game.h"

sfRenderWindow *create_window(int width, int heigth)
{
    sfRenderWindow *window;
    sfVideoMode vid_mode;

    vid_mode.width = width;
    vid_mode.height = heigth;
    vid_mode.bitsPerPixel = 32;
    window = sfRenderWindow_create(vid_mode, "My world", sfFullscreen, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    return (window);
}

static void scroll_handle(game_t *game)
{
    float zoom_speed = 0.05f;

    if (game->event.mouseWheelScroll.delta > 0){
        game->camera.camera_zoom += zoom_speed;
        if (game->camera.camera_zoom > MIN_CAMERA_ZOOM)
            game->camera.camera_zoom = MIN_CAMERA_ZOOM;
        return;
    }
    if (game->event.mouseWheelScroll.delta < 0) {
        game->camera.camera_zoom -= zoom_speed;
        if (game->camera.camera_zoom < MAX_CAMERA_ZOOM)
            game->camera.camera_zoom = MAX_CAMERA_ZOOM;
        return;
    }
}

static void event_handle(game_t *game)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(game->window);

    if (game->event.type == sfEvtKeyPressed
        && game->event.key.code == sfKeyEscape) {
        if (game->is_ingame)
            open_main_menu(game);
        else
            sfRenderWindow_close(game->window);
    }
    if (game->event.type == sfEvtMouseWheelScrolled && game->is_ingame)
        scroll_handle(game);
    if (game->event.type == sfEvtMouseButtonPressed)
        focus_text_input(game, &game->ui.file_input, &mouse);
    handle_text_input_event(game, &game->event);
}

static void poll_event(game_t *game)
{
    while (sfRenderWindow_pollEvent(game->window, &game->event)) {
        event_handle(game);
    }
}

//need some game info here
void display_help(void)
{
    printf("Game Info\n");
    printf("Usage: ./my_world\n\n");
    print_info_bug();
}

static void render_menu(game_t *game)
{
    if (game->menu_bg)
        sfRenderWindow_drawSprite(game->window, game->menu_bg, NULL);
    render_ui(game);
}

static void render_game(game_t *game)
{
    handle_keys(game);
    game_render(game);
    render_ui(game);
    render_text_input(game, &game->ui.file_input);
}

void destroy_everything(game_t *game)
{
    for (int i = 0; i < game->blocks_registry.registered_count; i++) {
        if (game->blocks_registry.blocks[i].texture != NULL) {
            sfTexture_destroy(game->blocks_registry.blocks[i].texture);
        }
    }
    destroy_ui(game);
    sfSprite_destroy(game->world_builder);
    sfSprite_destroy(game->selected_block.sprite);
    sfClock_destroy(game->input_delay);
    sfRenderWindow_destroy(game->window);
    free(game);
}

int main(int argc, char *argv[], char **env)
{
    game_t *game = malloc(sizeof(game_t));

    *game = (game_t){0};
    parser(argc, argv, env, game);
    init_all(game);
    while (sfRenderWindow_isOpen(game->window)) {
        sfRenderWindow_clear(game->window, sfColor_fromRGB(153, 255, 255));
        poll_event(game);
        update_buttons(game);
        if (game->is_ingame)
            render_game(game);
        else
            render_menu(game);
        sfRenderWindow_display(game->window);
    }
    destroy_everything(game);
    return 0;
}
