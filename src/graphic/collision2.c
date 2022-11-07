/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:07:48 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/07 16:49:43 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	get_y_with_x(t_data *data, float x, float pov)
{
	float	coef;

	coef = tan(pov);
	return (coef * (data->player->x - x) + data->player->y);
}

float	get_x_with_y(t_data *data, float y, float pov)
{
	float	coef;

	coef = 1 / tan(pov);
	return (coef * (data->player->y - y) + data->player->x);
}

float	get_fixed_ray_end(t_ray *ray, char dir, float pov)
{
	if (dir == 'y')
	{
		if (pov == PI || pov == 0)
			return (ray->y_end);
		if (pov < PI)
			return (ceil(ray->y_end - 1));
		else
			return (floor(ray->y_end + 1));
		return (ray->y_end);
	}
	if (pov == PI_ON_TWO || pov == THREE_PI_ON_TWO)
		return (ray->x_end);
	if (pov < PI_ON_TWO || pov > THREE_PI_ON_TWO)
		return (floor(ray->x_end + 1));
	else
		return (ceil(ray->x_end - 1));
	return (ray->x_end);
}

int	get_wall_dir(t_ray *ray, char dir, float pov)
{
	if (dir == 'y')
	{
		if (pov < PI)
			return (SO);
		else
			return (NO);
		return (ray->y_end);
	}
	if (pov < PI_ON_TWO || pov > THREE_PI_ON_TWO)
		return (WE);
	else
		return (EA);
	return (NO);
}
