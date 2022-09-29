/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:20:23 by aandric           #+#    #+#             */
/*   Updated: 2022/09/29 16:39:30 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUBD3D_H

/************************LIBS**************************/

# include "./libft/libft.h"
# include "./mlx/mlx.h"

/****************DEFINES_KEYBOARD*********************/

# define KB_D 2
# define KB_A 0
# define KB_W 13
# define KB_S 1
# define KB_LEFT 123
# define KB_RIGHT 124
# define ESCAPE_KC 53

typedef struct s_scene
{
	char	*tmp_line;
	int		tmp_width;
	int		height;
	int		width;
	char	*onedim;
	char	**twodim;
	int		collec;
	int		exit;
	int		startpos;
	int		time;
}			t_scene;

typedef struct s_player
{
	int		x;
	int		y;
	int		collec;
	int		i_steps_count;
	char	*steps_count;
}			t_player;

typedef struct s_sprites
{
	void	*mlx;
	void	*win;
	void	*NO_walls;
	void	*SO_walls;
	void	*WE_walls;
	void	*ES_walls;
}			t_sprites;


typedef struct s_data
{
	t_sprites	sprites;
	t_scene		scene;
	t_player	player;
}				t_data;

/*init data with scene*/
/* parse data*/
/*>> textures, colors*/


#endif