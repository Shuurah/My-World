/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** text_input.c
*/

#include "game.h"

static void init_bg_box(text_input_t *input)
{
    input->shape = sfRectangleShape_create();
    sfRectangleShape_setPosition(input->shape, input->position);
    sfRectangleShape_setSize(input->shape, input->size);
    sfRectangleShape_setFillColor(input->shape, sfColor_fromRGB(30, 30, 30));
    sfRectangleShape_setOutlineColor(input->shape, sfWhite);
    sfRectangleShape_setOutlineThickness(input->shape, 2);
}

static void init_text(text_input_t *input, sfFont *font)
{
    input->text = sfText_create();
    sfText_setFont(input->text, font);
    sfText_setCharacterSize(input->text, 20);
    sfText_setFillColor(input->text, sfWhite);
    sfText_setString(input->text, "");
    sfText_setPosition(input->text, (sfVector2f)
        {input->position.x + 6, input->position.y + 8});
}

static void init_placeholder(text_input_t *input, sfFont *font,
    char *placeholder_str)
{
    input->placeholder = sfText_create();
    sfText_setFont(input->placeholder, font);
    sfText_setCharacterSize(input->placeholder, 20);
    sfText_setFillColor(input->placeholder, sfColor_fromRGB(130, 130, 130));
    sfText_setString(input->placeholder, placeholder_str);
    sfText_setPosition(input->placeholder, (sfVector2f)
        {input->position.x + 6, input->position.y + 8});
}

void init_text_input(text_input_t *input, sfFloatRect *rect,
    char *placeholder_str, sfFont *font)
{
    input->position = (sfVector2f){rect->left, rect->top};
    input->size = (sfVector2f){rect->width, rect->height};
    input->length = 0;
    input->buffer[0] = '\0';
    input->is_focused = false;
    input->is_visible = true;
    init_bg_box(input);
    init_text(input, font);
    init_placeholder(input, font, placeholder_str);
}

void setup_file_input(game_t *game)
{
    init_text_input(&game->ui.file_input,
        &(sfFloatRect){
            20, game->window_y - 50,
            300, 40},
        "Enter filename...",
        game->ui.font);
}

void focus_text_input(game_t *game, text_input_t *input, sfVector2i *mouse)
{
    (void)game;
    input->is_focused = (mouse->x >= input->position.x &&
        mouse->x <= input->position.x + input->size.x &&
        mouse->y >= input->position.y &&
        mouse->y <= input->position.y + input->size.y);
    sfRectangleShape_setOutlineColor(input->shape,
        input->is_focused ? sfColor_fromRGB(100, 180, 255) : sfWhite);
}

static void get_unicode(sfEvent *event, text_input_t *input, game_t *game)
{
    sfUint32 c = event->text.unicode;

    if (c >= 32 && c < 127 && input->length < TEXT_INPUT_MAX - 1) {
        input->buffer[input->length] = (char) c;
        input->length++;
        input->buffer[input->length] = '\0';
        sfText_setString(input->text, input->buffer);
        free(game->file);
        game->file = strdup(input->buffer);
    }
}

void handle_text_input_event(game_t *game, sfEvent *event)
{
    text_input_t *input = &game->ui.file_input;

    if (!input->is_focused || !input->is_visible)
        return;
    if (event->type == sfEvtKeyPressed
        && event->key.code == sfKeyBackspace) {
        if (input->length > 0) {
            input->length--;
            input->buffer[input->length] = '\0';
            sfText_setString(input->text, input->buffer);
        }
        free(game->file);
        game->file = input->length > 0 ? strdup(input->buffer) : NULL;
        return;
    }
    if (event->type != sfEvtTextEntered)
        return;
    get_unicode(event, input, game);
}

void render_text_input(game_t *game, text_input_t *input)
{
    if (!input->is_visible)
        return;
    sfRenderWindow_drawRectangleShape(game->window, input->shape,
        NULL);
    if (input->length == 0)
        sfRenderWindow_drawText(game->window, input->placeholder,
            NULL);
    else
        sfRenderWindow_drawText(game->window, input->text, NULL);
}
