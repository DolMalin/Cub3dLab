# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 13:19:38 by aandric           #+#    #+#              #
#    Updated: 2022/10/12 17:07:53 by pdal-mol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			cub3d

LIBFT = ./libft/libft.a \

# MLX = ./mlx/libmlx.a \

PARSING_FILES 		=	data.c \
						parse_scene.c \
						get_features_from_scene.c \
				
CHECK_INPUT_FILES 	=	check_input.c \
						check_map.c \
						check_colors.c \
						check_textures.c \
						check_config_structure.c \

UTILS_FILES 		=	utils1.c \
						utils2.c \
						utils3.c \

SRC_FILES 			=	main.c \
						error.c \
			${addprefix parsing/, ${PARSING_FILES}} \
			${addprefix utils/, ${UTILS_FILES}} \
			${addprefix check_input/, ${CHECK_INPUT_FILES}}

## ======================= TO REMOVE ======================= ##
SRC_FILES_2 =	${addprefix parsing/, ${PARSING_FILES}} \
				${addprefix utils/, ${UTILS_FILES}} \
				${addprefix check_input/, ${CHECK_INPUT_FILES}}

HEADERS_2 = includes/cub3d.h unit-tests/test.h

## TEST PARSING
TEST_PARSING_FILES =	\
						test_parsing.c \
						test_functions.c \
						utils.c \
						
TEST_PARSING =			${addprefix unit-tests/, ${TEST_PARSING_FILES}}
SRC_PARSING = 			${addprefix src/, ${SRC_FILES_2}}\
						src/error.c \
						${TEST_PARSING}\
						
OBJS_PARSING = 			${SRC_PARSING:.c=.o}

## TEST INPUT
TEST_INPUT_FILES =		test_input.c \
						test_functions.c \
						utils.c\
					
TEST_INPUT =			${addprefix unit-tests/, ${TEST_INPUT_FILES}}
SRC_INPUT = 			${addprefix src/, ${SRC_FILES_2}}\
						src/error.c \
						${TEST_INPUT}
OBJS_INPUT = 			${SRC_INPUT:.c=.o}



## ========================================================= ##

SRC = 			${addprefix src/, ${SRC_FILES}}
OBJS = 			${SRC:.c=.o}
HEADERS = 		includes/cub3d.h

CMD = 			gcc
FLAGS = 		-Wall -Werror -Wextra  -g3 -fsanitize=address

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
test_parsing: 	$(OBJS_PARSING) libft $(LIBFT) Makefile
				$(CMD) ${FLAGS} $(OBJS_PARSING) $(LIBFT) -o test

test_input: 	$(OBJS_INPUT) libft $(LIBFT) Makefile
				$(CMD) ${FLAGS} $(OBJS_INPUT) $(LIBFT) -o test

testclean:
			rm -rf $(OBJS_PARSING) $(OBJS_INPUT)
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