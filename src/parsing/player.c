/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:14:26 by aandric           #+#    #+#             */
/*   Updated: 2022/11/04 17:58:19 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	get_player_pov(t_data *data)
{
	char		player_pov;

	player_pov = get_player_token(data);
	if (player_pov == 'N')
		return (M_PI_2);
	if (player_pov == 'S')
		return (3 * M_PI_2);
	if (player_pov == 'E')
		return (2 * M_PI);
	if (player_pov == 'W')
		return (M_PI);
	return (0);
}

float	get_player_start_pos(t_data *data, char axis)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (is_in_charset(data->map[i][j], "NSEW"))
			{
				if (axis == 'y')
					return ((float)i + (PRINT_COEF / 2) * 0.1);
				return ((float)j + (PRINT_COEF / 2) * 0.1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

t_player	*init_player(t_data *data)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		error(MEMALLOC);
	player->pov = get_player_pov(data);
	player->ray_coef_x = cos(player->pov);
	player->ray_coef_y = sin(player->pov);
	player->x = get_player_start_pos(data, 'x');
	player->y = get_player_start_pos(data, 'y');
	return (player);
}
