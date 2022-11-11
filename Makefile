# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 13:19:38 by aandric           #+#    #+#              #
#    Updated: 2022/11/11 18:00:12 by aandric          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = 			cub3d

LIBFT = ./libft/libft.a \

MLX = ./mlx/libmlx.a \

PARSING_FILES 		=	init_data.c \
						init_data2.c \
						player.c \
						parse_scene.c \
						get_features_from_scene.c \
						trim_config_line.c \
						get_map.c
				
CHECK_INPUT_FILES 	=	check_input.c \
						check_map.c \
						check_map2.c \
						check_colors.c \
						check_colors2.c \
						check_textures.c \
						check_config_structure.c \
						
ACTION_FILES 	=		run_game.c \
						move_player.c \
						move_player2.c \

GRAPHIC_FILES 	=		create_image.c \
						graphic_utils.c \
						raycasting.c	\
						collision.c		\
						collision2.c	\
						colors.c		\
						draw_walls.c

UTILS_FILES 		=	utils1.c \
						utils2.c \
						utils3.c \

SRC_FILES 			=	main.c \
						error.c \
			${addprefix parsing/, ${PARSING_FILES}} \
			${addprefix utils/, ${UTILS_FILES}} \
			${addprefix check_input/, ${CHECK_INPUT_FILES}}\
			${addprefix action/, ${ACTION_FILES}} \
			${addprefix graphic/, ${GRAPHIC_FILES}} \

SRC = 			${addprefix src/, ${SRC_FILES}}
OBJS = 			${SRC:.c=.o}
HEADERS = 		includes/cub3d.h

CMD = 			gcc
FLAGS = 		-Wall -Werror -Wextra  -O3

LIB =			./libft/libft.a ./mlx/libmlx.a

FLAGSX =		-L mlx -l mlx -framework OpenGL -framework Appkit

all: 			library $(NAME)

%.o:			%.c $(HEADERS) $(LIB)
				$(CMD) $(FLAGS) -Imlx -c $< -o $@

$(NAME): 		$(OBJS) $(LIB) Makefile
				$(CMD) $(FLAGS) $(OBJS) $(LIB) -o $(NAME) $(FLAGSX)

library: 
					make -C ./libft
					make -C ./mlx

clean:
		rm -rf $(OBJS)
		make clean -C ./libft
		make clean -C ./mlx

fclean: clean
		rm -rf $(NAME)
		make fclean -C ./libft
		make clean -C ./mlx
		

re: fclean all

.PHONY: libft mlx clean all re fclean