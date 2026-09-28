/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** save_and_load.c
*/

#include "game.h"

static void write_to_file(int x, int y, game_t *game, FILE *file)
{
    for (int z = 0; z < game->current_world_heigth; z++)
        fwrite(&game->world[x][y][z], sizeof(int), 1, file);
}

int save_world_to_file(game_t *game, char *filename)
{
    char *extention = my_strjoin_separator(filename, ".legend", '\0');
    char *world_name = my_strjoin_separator("save", extention, '/');
    FILE *file = fopen(world_name, "wb");

    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", world_name);
        free(extention);
        free(world_name);
        return -1;
    }
    fwrite(&game->current_world_size, sizeof(int), 1, file);
    fwrite(&game->current_world_heigth, sizeof(int), 1, file);
    for (int x = 0; x < game->current_world_size; x++){
        for (int y = 0; y < game->current_world_size; y++)
            write_to_file(x, y, game, file);
    }
    fclose(file);
    free(extention);
    free(world_name);
    return 0;
}

static int game_world_save(game_t *game, FILE *file, int x, int y)
{
    for (int z = 0; z < game->current_world_heigth; z++) {
        if (fread(&game->world[x][y][z], sizeof(int), 1, file) != 1) {
            fprintf(stderr, "Error: Failed to read block at [%d][%d][%d]\n",
                x, y, z);
            return -1;
        }
    }
    return 0;
}

static int read_and_error(game_t *game, FILE *file)
{
    if (!file)
        return -1;
    fread(&game->current_world_size, sizeof(int), 1, file);
    fread(&game->current_world_heigth, sizeof(int), 1, file);
    if (game->current_world_size > WORLD_SIZE
        || game->current_world_heigth > WORLD_HEIGHT) {
        fprintf(stderr, "Error: World too large. File: %dx%d, Max: %dx%d\n",
            game->current_world_size, game->current_world_heigth,
            WORLD_SIZE, WORLD_HEIGHT);
        return -1;
    }
    return 0;
}

static int free_world(FILE *file, char *extention, char *world_name)
{
    fclose(file);
    free(extention);
    free(world_name);
    return 0;
}

static int size_world(game_t *game, int x, int y)
{
    for (int z = 0; z < WORLD_HEIGHT; z++)
        game->world[x][y][z] = AIR;
    return 0;
}

static int print_world_size(game_t *game, char *filename)
{
    printf("World loaded from save/%s (%d blocks)\n", filename,
        game->current_world_size * game->current_world_size
        * game->current_world_heigth);
    return 0;
}

int load_world_from_file(game_t *game, char *filename)
{
    char *extention = my_strjoin_separator(filename, ".legend", '\0');
    char *world_name = my_strjoin_separator("save", extention, '/');
    FILE *file = fopen(world_name, "rb");

    if (read_and_error(game, file) == -1) {
        fprintf(stderr, "Error: Could not open or read file %s\n", world_name);
        free(extention);
        free(world_name);
        if (file)
            fclose(file);
        return -1;
    }
    for (int x = 0; x < WORLD_SIZE; x++)
        for (int y = 0; y < WORLD_SIZE; y++)
            size_world(game, x, y);
    for (int x = 0; x < game->current_world_size; x++)
        for (int y = 0; y < game->current_world_size; y++)
            game_world_save(game, file, x, y);
    free_world(file, extention, world_name);
    return print_world_size(game, filename);
}

void load_world(game_t *game)
{
    if (game->file && strlen(game->file) > 3)
        load_world_from_file(game, game->file);
    else
        printf("your load name need at least 4 character\n");
    game->ui.file_input.buffer[0] = '\0';
    game->ui.file_input.length = 0;
    sfText_setString(game->ui.file_input.text, "");
    free(game->file);
    game->file = NULL;
}

void save_world(game_t *game)
{
    if (game->file && strlen(game->file) > 3)
        save_world_to_file(game, game->file);
    else
        printf("your save name need at least 4 character\n");
    game->ui.file_input.buffer[0] = '\0';
    game->ui.file_input.length = 0;
    sfText_setString(game->ui.file_input.text, "");
    free(game->file);
    game->file = NULL;
}
