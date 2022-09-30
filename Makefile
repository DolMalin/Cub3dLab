# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 13:19:38 by aandric           #+#    #+#              #
#    Updated: 2022/09/30 16:01:02 by aandric          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = 			cub3d

LIBFT = ./libft/libft.a \

MLX = ./mlx/libmlx.a \

PARSING_FILES =	data.c \
				check_input.c \
				parse_scene.c
				
UTILS_FILES =	utils1.c

SRC_FILES =  	main.c \
				${addprefix parsing/, ${PARSING_FILES}} \
				${addprefix utils/, ${UTILS_FILES}}

SRC = 			${addprefix src/, ${SRC_FILES}}
OBJS = 			${SRC:.c=.o}
HEADERS = 		includes/cub3d.h

CMD = 			gcc
FLAGS = 		-Wall -Werror -Wextra

%.o: 			%.c $(HEADERS)
				$(CMD) $(FLAGS) -c $< -o $@
all: libft $(NAME)
libft:
		make -C ./libft
mlx:
		make -C ./mlx

$(NAME): 		$(OBJS) $(LIBFT) Makefile
				$(CMD) ${FLAGS} $(OBJS) $(LIBFT) -o $(NAME)

clean:
		rm -rf $(OBJS)
		make clean -C ./libft
		make clean -C ./mlx

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: libft mlx clean all re fclean