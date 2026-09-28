/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** button_handler.c
*/

#include "game.h"

static void button_reset_camera(game_t *game)
{
    game->camera.camera_x = 800;
    game->camera.camera_y = 300;
    game->camera.camera_zoom = 0.5f;
    game->camera.rotation = 0;
}

static bool is_mouse_over_button(button_t *button, sfVector2i *mouse_pos)
{
    return (mouse_pos->x >= button->position.x &&
        mouse_pos->x <= button->position.x + button->size.x &&
        mouse_pos->y >= button->position.y &&
        mouse_pos->y <= button->position.y + button->size.y);
}

static void set_button_text(button_t *button, char *text, game_t *game)
{
    sfFloatRect textBounds;
    sfVector2f textPos;

    button->text = sfText_create();
    sfText_setString(button->text, text);
    sfText_setFont(button->text, game->ui.font);
    sfText_setCharacterSize(button->text, 20);
    sfText_setFillColor(button->text, sfWhite);
    textBounds = sfText_getLocalBounds(button->text);
    textPos = (sfVector2f){ button->position.x + (button->size.x -
            textBounds.width) / 2 - textBounds.left,
        button->position.y + (button->size.y -
            textBounds.height) / 2 - textBounds.top};
    sfText_setPosition(button->text, textPos);
}

button_t *create_button(sfFloatRect *rect, char *text,
    void (*callback)(game_t *), game_t *game)
{
    button_t *button = malloc(sizeof(button_t));

    button->position = (sfVector2f){rect->left, rect->top};
    button->size = (sfVector2f){rect->width, rect->height};
    button->state = BUTTON_IDLE;
    button->on_click = callback;
    button->is_visible = true;
    button->idle_color = sfColor_fromRGB(70, 70, 70);
    button->hover_color = sfColor_fromRGB(100, 100, 100);
    button->pressed_color = sfColor_fromRGB(50, 50, 50);
    button->shape = sfRectangleShape_create();
    sfRectangleShape_setPosition(button->shape, button->position);
    sfRectangleShape_setSize(button->shape, button->size);
    sfRectangleShape_setFillColor(button->shape, button->idle_color);
    sfRectangleShape_setOutlineColor(button->shape, sfWhite);
    sfRectangleShape_setOutlineThickness(button->shape, 2);
    set_button_text(button, text, game);
    return button;
}

static void check_mouse_click(game_t *game,
    bool mouse_clicked, button_t *button)
{
    if (mouse_clicked) {
        button->state = BUTTON_PRESSED;
        sfRectangleShape_setFillColor(button->shape, button->pressed_color);
    } else {
        if (button->state == BUTTON_PRESSED && button->on_click) {
            button->on_click(game);
        }
        button->state = BUTTON_HOVER;
        sfRectangleShape_setFillColor(button->shape, button->hover_color);
    }
}

void update_buttons(game_t *game)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(game->window);
    bool mouse_clicked = sfMouse_isButtonPressed(sfMouseLeft);
    button_t *button;

    for (int i = 0; i < game->ui.button_count; i++) {
        button = &game->ui.buttons[i];
        if (!button->is_visible)
            continue;
        if (is_mouse_over_button(button, &mouse_pos)) {
            check_mouse_click(game, mouse_clicked, button);
        } else {
            button->state = BUTTON_IDLE;
            sfRectangleShape_setFillColor(button->shape, button->idle_color);
        }
    }
}

void render_ui(game_t *game)
{
    button_t *button;

    for (int i = 0; i < game->ui.button_count; i++) {
        button = &game->ui.buttons[i];
        if (!button->is_visible)
            continue;
        sfRenderWindow_drawRectangleShape(game->window, button->shape, NULL);
        sfRenderWindow_drawText(game->window, button->text, NULL);
    }
    if (game->is_ingame)
        sfRenderWindow_drawSprite(game->window,
            game->selected_block.sprite, NULL);
}

void destroy_ui(game_t *game)
{
    for (int i = 0; i < game->ui.button_count; i++) {
        sfRectangleShape_destroy(game->ui.buttons[i].shape);
        sfText_destroy(game->ui.buttons[i].text);
    }
    free(game->ui.buttons);
    if (game->ui.font)
        sfFont_destroy(game->ui.font);
}
