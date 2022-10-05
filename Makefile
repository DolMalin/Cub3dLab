# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 13:19:38 by aandric           #+#    #+#              #
#    Updated: 2022/10/05 15:49:32 by aandric          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = 			cub3d

LIBFT = ./libft/libft.a \

# MLX = ./mlx/libmlx.a \

PARSING_FILES 		=	data.c \
						parse_scene.c \
						get_features_from_scene.c \
				
CHECK_INPUT_FILES 	=	check_input.c \

UTILS_FILES 		=	utils1.c \
						utils2.c \

SRC_FILES 			=	main.c \
			${addprefix parsing/, ${PARSING_FILES}} \
			${addprefix utils/, ${UTILS_FILES}} \
			${addprefix check_input/, ${CHECK_INPUT_FILES}}

## ======================= TO REMOVE ======================= ##
SRC_FILES_2 =	${addprefix parsing/, ${PARSING_FILES}} \
				${addprefix utils/, ${UTILS_FILES}} \
				${addprefix check_input/, ${CHECK_INPUT_FILES}}

TEST_PARSING = 	main.c \
				parsing.c \
				utils.c \
				
TEST_UNITS =	${addprefix unit-tests/, ${TEST_PARSING}}

SRC_2 = 		${addprefix src/, ${SRC_FILES_2}}\
				${TEST_UNITS}

HEADERS_2 = includes/cub3d.h unit-tests/test.h
OBJS_2 = 			${SRC_2:.c=.o}
## ========================================================= ##

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

				
## ======================= TO REMOVE ======================= ##
test: 			$(OBJS_2) libft $(LIBFT) Makefile
				$(CMD) ${FLAGS} $(OBJS_2) $(LIBFT) -o test

testclean:
			rm -rf $(OBJS_2)
			make clean -C ./libft
			make clean -C ./mlx
			rm -rf test
## ========================================================= ##

clean:
		rm -rf $(OBJS)
		make clean -C ./libft
		make clean -C ./mlx

fclean: clean
		rm -rf $(NAME)
		make fclean -C ./libft
		make fclean -C ./mlx
		

re: fclean all

.PHONY: libft mlx clean all re fclean