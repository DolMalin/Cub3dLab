/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:07:48 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/02 17:35:29 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	get_y_with_x(t_data *data, float x)
{
	float coef;

	coef = tan(data->player->pov);
	return (coef * (data->player->x - x) + data->player->y);
	// return (data->player->y + (data->player->x - x) / data->player->ray_coef_x * data->player->ray_coef_y);	
}

float	get_x_with_y(t_data *data, float y)
{
	float coef;
	
	coef = 1 / tan(data->player->pov);
	return (coef * (data->player->y - y) + data->player->x);
	// return (data->player->x + (data->player->y - y) / data->player->ray_coef_y * data->player->ray_coef_x);
	
}


float	get_fixed_ray_end(t_data *data, t_ray *ray, char dir)
{
	if (dir == 'y')
	{
		if (data->player->pov == M_PI || data->player->pov == 0)
			return (ray->y_end);
		if (data->player->pov < M_PI)
			return (ceil(ray->y_end - 1));
		else
			return (floor(ray->y_end + 1));
		return (ray->y_end);
	}
	if (data->player->pov == M_PI_2 || data->player->pov == 3 * M_PI_2)
		return (ray->x_end);
	if (data->player->pov < M_PI_2 || data->player->pov > 3 * M_PI_2)
		return (floor(ray->x_end + 1));
	else
		return (ceil(ray->x_end - 1));
	return (ray->x_end);
}
