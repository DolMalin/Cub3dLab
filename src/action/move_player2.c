/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:40:34 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/01 16:25:35 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	get_player_token(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (is_in_charset(data->map[i][j], "NSEW"))
			{
				if (is_in_charset(data->map[i][j], "N"))
					return ('N');
				else if (is_in_charset(data->map[i][j], "S"))
					return ('S');
				else if (is_in_charset(data->map[i][j], "E"))
					return ('E');
				return ('W');
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	rotate_right(t_data **data)
{
	(*data)->player->pov -= FOV_STEP;
	if ((*data)->player->pov < 0)
		(*data)->player->pov += 2 * M_PI;
	///////
	(*data)->player->ray_coef_x = cos((*data)->player->pov);
	(*data)->player->ray_coef_y = sin((*data)->player->pov);
}

void	rotate_left(t_data **data)
{
	(*data)->player->pov += FOV_STEP;
	if ((*data)->player->pov >= 2 * M_PI)
		(*data)->player->pov -= 2 * M_PI;
	//////
	(*data)->player->ray_coef_x = cos((*data)->player->pov);
	(*data)->player->ray_coef_y = sin((*data)->player->pov);
}
