/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:38:35 by aandric           #+#    #+#             */
/*   Updated: 2022/09/30 13:13:28 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ********************************LIBS************************************** */

# include "../libft/libft.h"
# include "../mlx/mlx.h"

/* *****************************DEFINES_KEYBOARD***************************** */

# define KB_D 2
# define KB_A 0
# define KB_W 13
# define KB_S 1
# define KB_LEFT 123
# define KB_RIGHT 124
# define ESCAPE_KC 53

# define NO 0
# define SO 1
# define WE 2
# define EA 3

# define FLOOR 0
# define CEIL 1

typedef struct s_data
{
	char			**textures_path;
	/* Use of unsigned array of size 3 because RGB contains 3 values between 0 and 255*/
	unsigned char	*colors[3];
	char			**map;
}				t_data;

/* **********************************PARSING********************************* */
int	check_input(int ac, char **av);

#endif