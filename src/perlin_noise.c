/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** perlin_noise.c
*/

#include "game.h"

int noise2(int x, int y, game_t *game)
{
    int tmp = DEFAULT_HASH[(y + game->seed) % 256];

    return DEFAULT_HASH[(tmp + x) % 256];
}

float lin_inter(float x, float y, float s)
{
    return x + s * (y - x);
}

float smooth_inter(float x, float y, float s)
{
    return lin_inter(x, y, s * s * (3 - 2 * s));
}

float noise2d(float x, float y, game_t *game)
{
    int x_int = x;
    int y_int = y;
    float x_frac = x - x_int;
    float y_frac = y - y_int;
    int s = noise2(x_int, y_int, game);
    int t = noise2(x_int + 1, y_int, game);
    int u = noise2(x_int, y_int + 1, game);
    int v = noise2(x_int + 1, y_int + 1, game);
    float low = smooth_inter(s, t, x_frac);
    float high = smooth_inter(u, v, x_frac);

    return smooth_inter(low, high, y_frac);
}

float perlin2d(sfVector2f *pos, float freq, int depth, game_t *game)
{
    float xa = pos->x * freq;
    float ya = pos->y * freq;
    float amp = 1.0;
    float fin = 0;
    float div = 0.0;

    for (int i = 0; i < depth; i++) {
        div += 256 * amp;
        fin += noise2d(xa, ya, game) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }
    return fin / div;
}
