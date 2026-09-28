/*
** EPITECH PROJECT, 2025
** game.h
** File description:
** header for game
*/

#ifndef GAME_H_
    #define GAME_H_
    #define PI 3.14159265358979323846f
    #include <stdbool.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <stdarg.h>
    #include <SFML/Graphics.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <math.h>
    #include <time.h>

    #define WORLD_HEIGHT 20
    #define WORLD_SIZE 64

    #define TERRAIN_MIN 6
    #define TERRAIN_MAX 18
    #define TERRAIN_RANGE (TERRAIN_MAX - TERRAIN_MIN)
    #define TERRAIN_FREQ 0.015f //0.008f
    #define TERRAIN_DEPTH 4
    #define SEA_LEVEL 10

    #define SCREEN_LEN 1920
    #define SCREEN_HEIGHT 1080

    #define MAX_CAMERA_ZOOM 0.25f
    #define MIN_CAMERA_ZOOM 3.0f
    #define CAMERA_SPEED 5.0f
    #define SCALE 4
    #define INPUT_DELAY 0.1f

    #define MENU_BTN_START 26
    #define MENU_BTN_SETTINGS 27
    #define MENU_BTN_QUIT 28
    #define MENU_BTN_SMALL 29
    #define MENU_BTN_MEDIUM 30
    #define MENU_BTN_LARGE 31
    #define MENU_BTN_BACK 32
    #define MENU_BTN_COUNT 7

    #define TOTAL_BUTTON 26 + MENU_BTN_COUNT

    #define TEXT_INPUT_MAX 32

    #define MAX_BLOCK_TYPES 9
    #define AIR 1
    #define TILE 2
    #define DIRT 3
    #define GRASS 4
    #define STONE 5
    #define BEDROCK 6
    #define WATER 7
    #define GLASS 8

typedef struct game_s game_t;

typedef enum button_state_s {
    BUTTON_IDLE,
    BUTTON_HOVER,
    BUTTON_PRESSED
} button_state_t;

typedef struct button_s {
    sfRectangleShape *shape;
    sfText *text;
    sfVector2f position;
    sfVector2f size;
    button_state_t state;
    void (*on_click)(game_t *game);
    bool is_visible;
    sfColor idle_color;
    sfColor hover_color;
    sfColor pressed_color;
} button_t;

typedef struct text_input_s {
    sfRectangleShape *shape;
    sfText *text;
    sfText *placeholder;
    char buffer[TEXT_INPUT_MAX];
    int length;
    bool is_focused;
    bool is_visible;
    sfVector2f position;
    sfVector2f size;
} text_input_t;

typedef struct ui_s {
    button_t *buttons;
    int button_count;
    sfFont *font;
    text_input_t file_input;
} ui_t;

typedef struct block_properties_s {
    int id;
    bool is_transparent;
    int size;
    sfTexture *texture;
} block_properties_t;

typedef struct block_registry_s {
    block_properties_t blocks[MAX_BLOCK_TYPES];
    int registered_count;
} block_registry_t;

typedef struct camera_cord_s {
    float camera_zoom;
    float camera_speed;
    float camera_x;
    float camera_y;
    int rotation;
} camera_cord_t;

typedef struct selected_s {
    int id_replace;
    int x;
    int y;
    int z;
    sfSprite *sprite;
} selected_t;

struct game_s {
    int world[WORLD_SIZE][WORLD_SIZE][WORLD_HEIGHT];
    sfRenderWindow *window;
    sfEvent event;
    block_registry_t blocks_registry;
    sfSprite *world_builder;
    float world_builder_x;
    float world_builder_y;
    camera_cord_t camera;
    sfClock *input_delay;
    int layer_displayed;
    int current_world_size;
    int current_world_heigth;
    ui_t ui;
    selected_t selected_block;
    sfTexture *selected_texture;
    int seed;
    int window_x;
    int window_y;
    bool is_ingame;
    sfSprite *menu_bg;
    sfTexture *menu_bg_texture;
    char *file;
};

static const int DEFAULT_HASH[256] = {208, 34, 231, 213, 32, 248, 233, 56, 161,
    78, 24, 140, 71, 48, 140, 254, 245, 255, 247, 247, 40, 185, 248, 251, 245,
    28, 124, 204, 204, 76, 36, 1, 107, 28, 234, 163, 202, 224, 245, 128, 167,
    204, 9, 92, 217, 54, 239, 174, 173, 102, 193, 189, 190, 121, 100, 108,
    167, 44, 43, 77, 180, 204, 8, 81, 70, 223, 11, 38, 24, 254, 210, 210,
    177, 32, 81, 195, 243, 125, 8, 169, 112, 32, 97, 53, 195, 13, 203, 9,
    47, 104, 125, 117, 114, 124, 165, 203, 181, 235, 193, 206, 70, 180,
    174, 0, 167, 181, 41, 164, 30, 116, 127, 198, 245, 146, 87, 224, 149,
    206, 57, 4, 192, 210, 65, 210, 129, 240, 178, 105, 228, 108, 245, 148,
    140, 40, 35, 195, 38, 58, 65, 207, 215, 253, 65, 85, 208, 76, 62, 3,
    237, 55, 89, 232, 50, 217, 64, 244, 157, 199, 121, 252, 90, 17, 212,
    203, 149, 152, 140, 187, 234, 177, 73, 174, 193, 100, 192, 143, 97, 53,
    145, 135, 19, 103, 13, 90, 135, 151, 199, 91, 239, 247, 33, 39, 145,
    101, 120, 99, 3, 186, 86, 99, 41, 237, 203, 111, 79, 220, 135, 158, 42,
    30, 154, 120, 67, 87, 167, 135, 176, 183, 191, 253, 115, 184, 21, 233,
    58, 129, 233, 142, 39, 128, 211, 118, 137, 139, 255, 114, 20, 218, 113,
    154, 27, 127, 246, 250, 1, 8, 198, 250, 209, 92, 222, 173, 21, 88, 102,
    219};

char *my_strjoin_separator(char *s1, char *s2, char separator);

void selected_x_negative(game_t *game);
void selected_x_positive(game_t *game);
void selected_y_negative(game_t *game);
void selected_y_positive(game_t *game);
void selected_z_negative(game_t *game);
void selected_z_positive(game_t *game);

float perlin2d(sfVector2f *pos, float freq, int depth, game_t *game);

void place_block(game_t *game);
void destroy_block(game_t *game);

void zoom_in(game_t *game);
void zoom_out(game_t *game);

void select_block_grass(game_t *game);
void select_block_stone(game_t *game);
void select_block_tile(game_t *game);
void select_block_water(game_t *game);
void select_block_bedrock(game_t *game);
void select_block_dirt(game_t *game);
void select_block_glass(game_t *game);

void parser(int argc, char *argv[], char **env, game_t *game);
int write_err(char *message, int return_value);
void display_help(void);
void init_block_registry(game_t *game);
void register_block(block_properties_t *properties, game_t *game);
block_properties_t *get_block_properties(int block_id, game_t *game);
void game_render(game_t *game);
int has_display(char **env);
sfRenderWindow *create_window(int width, int heigth);
void handle_keys(game_t *game);
void init_all(game_t *game);
void create_world(game_t *game);
void rotate_coords(int *x, int *y, int rotation, game_t *game);

void go_down_layer(game_t *game);
void go_up_layer(game_t *game);
void turn_left(game_t *game);
void turn_right(game_t *game);
int save_world_to_file(game_t *game, char *filename);
int load_world_from_file(game_t *game, char *filename);
void load_world(game_t *game);
void save_world(game_t *game);
void print_info_bug(void);

void render_text_input(game_t *game, text_input_t *input);
void handle_text_input_event(game_t *game, sfEvent *event);
void setup_file_input(game_t *game);
void focus_text_input(game_t *game, text_input_t *input, sfVector2i *mouse);
void init_menu_buttons(game_t *game);
void open_main_menu(game_t *game);
void quit_game(game_t *game);

button_t *create_button(sfFloatRect *rect, char *text,
    void (*callback)(game_t *), game_t *game);
void init_ui(game_t *game);
void destroy_ui(game_t *game);
void render_ui(game_t *game);
void update_buttons(game_t *game);
#endif
