/*
** EPITECH PROJECT, 2025
** tty check
** File description:
** check_tty.c
*/

#include "game.h"

int has_display(char **env)
{
    int i = 0;

    while (env[i]) {
        if (strncmp(env[i], "DISPLAY=", 8) == 0)
            return 1;
        i++;
    }
    return 0;
}
