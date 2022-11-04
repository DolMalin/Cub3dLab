/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:44:04 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/04 15:10:13 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	put_player_to_minimap(t_data *data)
{
	my_mlx_pixel_put(
		data->image,
		(data->player->x * PRINT_COEF) + 20,
		(data->player->y * PRINT_COEF) + 20,
		0xFFFFF
		);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->image->ptr, 0, 0);
}

static void	put_mini_map_to_image(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				print_bigger(data->image, j, i, 0x34A145);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->image->ptr, 0, 0);
}

void	put_background_to_image(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			if (i / (WIN_HEIGHT * 0.5) <= 1)
				my_mlx_pixel_put(data->image, j, i, data->color_ceil);
			if (i / (WIN_HEIGHT * 0.5) > 1)
				my_mlx_pixel_put(data->image, j, i, data->color_floor);
			j++;
		}
		i++;
	}
	put_player_to_minimap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->image->ptr, 0, 0);
}

int	create_image(t_data *data)
{
	put_background_to_image(data);
	raycasting(data);
	put_mini_map_to_image(data);
	put_player_to_minimap(data);
	// mlx_put_image_to_window(data->mlx, data->mlx_win, data->textures[NO]->ptr, 0, 0);
	// mlx_put_image_to_window(data->mlx, data->mlx_win, data->textures[EA]->ptr, 100, 0);
	return (0);
}
