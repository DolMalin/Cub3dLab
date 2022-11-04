/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:07:48 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/04 17:50:39 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	get_y_with_x(t_data *data, float x)
{
	float	coef;

	coef = tan(data->player->pov);
	return (coef * (data->player->x - x) + data->player->y);
}

float	get_x_with_y(t_data *data, float y)
{
	float	coef;

	coef = 1 / tan(data->player->pov);
	return (coef * (data->player->y - y) + data->player->x);
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
	if (data->player->pov == M_PI_2 || data->player->pov == data->precomputed->radians[THREE_PI_ON_TWO])
		return (ray->x_end);
	if (data->player->pov < M_PI_2 || data->player->pov > data->precomputed->radians[THREE_PI_ON_TWO])
		return (floor(ray->x_end + 1));
	else
		return (ceil(ray->x_end - 1));
	return (ray->x_end);
}

int	get_wall_dir(t_data *data, t_ray *ray, char dir)
{
	if (dir == 'y')
	{
		if (data->player->pov < M_PI)
			return (SO);
		else
			return (NO);
		return (ray->y_end);
	}
	if (data->player->pov < M_PI_2 || data->player->pov > data->precomputed->radians[THREE_PI_ON_TWO])
		return (WE);
	else
		return (EA);
	return (NO);
}
