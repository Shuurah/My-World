/*
** EPITECH PROJECT, 2026
** my_strjoin_separator
** File description:
** snprintf command
*/

#include "game.h"

static int fill_result(char *result, char *s1, char *s2, char separator)
{
    int i = 0;
    int j = 0;

    while (s1[i]){
        result[i] = s1[i];
        i++;
    }
    if (separator != '\0'){
        result[i] = separator;
        i++;
    }
    while (s2[j]){
        result[i] = s2[j];
        i++;
        j++;
    }
    return i;
}

char *my_strjoin_separator(char *s1, char *s2, char separator)
{
    int len = strlen(s1) + strlen(s2) + 1;
    char *result = malloc(sizeof(char) * (len + 1));
    int end = 0;

    if (!result)
        return NULL;
    end = fill_result(result, s1, s2, separator);
    result[end] = '\0';
    return result;
}
