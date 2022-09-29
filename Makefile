# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 13:19:38 by aandric           #+#    #+#              #
#    Updated: 2022/09/29 14:20:34 by aandric          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = 			cub3d

LIBFT = ./libft/libft.a \

MLX = ./mlx/libmlx.a \

SRC_FILES =  	main.c \
				cub3d.c \

SRC = 			${addprefix src/, ${SRC_FILES}}
OBJS = 			${SRC:.c=.o}
HEADERS = 		includes/cub3d.h

CMD = 			gcc
FLAGS = 		-Wall -Werror -Wextra -I mlx

%.o: 			%.c $(HEADERS)
				$(CMD) $(FLAGS) -c $< -o $@
all: libft mlx $(NAME)
libft:
		make -C ./libft
mlx:
		make -C ./mlx

$(NAME): 		$(OBJS) $(LIBFT) $(MLX) Makefile
				$(CMD) ${FLAGS} $(OBJS) $(LIBFT) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
		rm -rf $(OBJS)
		make clean -C ./libft
		make clean -C ./mlx

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: libft mlx clean all re fclean