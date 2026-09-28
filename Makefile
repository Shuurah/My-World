##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## compile the lib and basic rules
##

CC	= epiclang

CFLAGS = -I include/

EPICLANGFLAGS = -Wall -Wextra -I include/

MEMORYLEAKSFLAGS = -fsanitize=address

MATHFLAGS = -lm 

LDFLAGS = -L. -lcsfml-system -lcsfml-window -lcsfml-graphics

ARG = -o $(NAME)

SRC	= lib/my_strjoin_separator.c \
	src/button_action/layer.c \
	src/button_action/main_menu.c \
	src/button_action/selection.c \
	src/asset_init.c \
	src/blocks_handler.c \
	src/blocks_registry.c \
	src/blocks_selecte.c \
	src/button_handler.c \
	src/check_tty.c \
	src/game_render.c \
	src/key_handler.c \
	src/perlin_noise.c \
	src/program_init.c \
	src/save_and_load.c \
	src/text_input.c \
	src/window.c \
	src/world_loading.c \

OBJ 	= $(SRC:.c=.o)

NAME	= my_world

all:	compile

compile: $(OBJ)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(ARG) $(MATHFLAGS)

debug: $(OBJ)
	@$(CC) $(LDFLAGS) $(EPICLANGFLAGS) $(MEMORYLEAKSFLAGS) $(OBJ) $(ARG) $(MATHFLAGS) -g

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

.PHONY: fclean all
re: fclean all
