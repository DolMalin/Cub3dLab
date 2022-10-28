/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:07:48 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/10/28 16:46:19 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	get_y_with_x(t_data *data, float x)
{
	return (tan(data->player->pov) * (data->player->x - x) + data->player->y);
}

float	get_x_with_y(t_data *data, float y)
{
	return ((data->player->y - y) / tan(data->player->pov) + data->player->x);
}


float	get_fixed_ray_end(t_data *data, t_ray *ray, char dir)
{
	if (dir == 'y')
	{
		if (data->player->pov <= M_PI)
			return (ceil(ray->y_end - 1));
		else
			return (floor(ray->y_end + 1));
		return (ray->y_end);
	}
	if (data->player->pov <= M_PI_2 || data->player->pov >= 3 * M_PI_2)
		return (floor(ray->x_end + 1));
	else
		return (ceil(ray->x_end - 1));
	return (ray->x_end); // case when pov = 0 || PI || 3 * PI / 4 || PI / 2
}
