/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:00:31 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/07 16:27:36 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_bool	check_collision_y(t_data *data, t_ray *ray, float pov)
{
	if (ray->y_end == 0 || ray->y_end == array_len((void **)data->map))
		return (true);
	if (pov > 0 && pov <= M_PI_2)
		if (data->map[(int)(ray->y_end - 1)][(int)floor(ray->x_end)] == '1')
			return (true);
	if (pov >= M_PI_2 && pov < M_PI)
		if (data->map[(int)(ray->y_end - 1)][(int)floor(ray->x_end)] == '1')
			return (true);
	if (pov > M_PI && pov <= data->precomputed->radians[THREE_PI_ON_TWO])
		if (data->map[(int)(ray->y_end)][(int)floor(ray->x_end)] == '1')
			return (true);
	if (pov > data->precomputed->radians[THREE_PI_ON_TWO])
		if (data->map[(int)(ray->y_end)][(int)floor(ray->x_end)] == '1')
			return (true);
	return (false);
}

static t_bool	check_collision_x(t_data *data, t_ray *ray, float pov)
{
	if (pov == 0 || pov == M_PI)
		if (data->map[(int)ray->y_end][(int)ray->x_end] == '1')
			return (true);
	if (ray->x_end == 0 || ray->x_end
		== ft_strlen(data->map[(int)floor(ray->y_end)]))
		return (true);
	if (pov >= 0 && pov <= M_PI_2)
		if (data->map[(int)floor(ray->y_end)][(int)(ray->x_end)] == '1')
			return (true);
	if (pov > M_PI_2 && pov <= M_PI)
		if (data->map[(int)floor(ray->y_end)][(int)(ray->x_end - 1)] == '1')
			return (true);
	if (pov >= M_PI && pov <= data->precomputed->radians[THREE_PI_ON_TWO])
		if (data->map[(int)floor(ray->y_end)][(int)(ray->x_end - 1)] == '1')
			return (true);
	if (pov > data->precomputed->radians[THREE_PI_ON_TWO])
		if (data->map[(int)floor(ray->y_end)][(int)(ray->x_end)] == '1')
			return (true);
	return (false);
}


static t_ray	*get_collision_y(t_data *data, float pov)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		error(MEMALLOC);
	ray->x_end = 1000000;
	ray->y_end = data->player->y;
	ray->angle = pov;
	ray->coll = false;
	while (!ray->coll)
	{
		ray->y_end = get_fixed_ray_end(data, ray, 'y', pov);
		ray->dir = get_wall_dir(data, ray, 'y', pov);
		if (pov == M_PI || pov == 0)
			return (ray);
		ray->x_end = get_x_with_y(data, ray->y_end, pov);
		// if (ray->x_end >= ft_strlen(data->map[(int)ray->y_end])
		if (ray->x_end >= data->precomputed->map_lines_len[(int)ray->y_end]
			|| ray->x_end < 0)
			return (ray);
		if (ray->y_end > array_len((void **)data->map) || ray->y_end < 0)
			return (ray);
		if (check_collision_y(data, ray, pov))
			ray->coll = true;
		
	}
	return (ray);
}

static t_ray	*get_collision_x(t_data *data, float pov)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		error(MEMALLOC);
	ray->x_end = data->player->x;
	ray->y_end = 1000000;
	ray->angle = pov;
	ray->coll = false;
	while (!ray->coll)
	{
		ray->x_end = get_fixed_ray_end(data, ray, 'x', pov);
		ray->dir = get_wall_dir(data, ray, 'x', pov);
		if (pov == M_PI_2 || pov == data->precomputed->radians[THREE_PI_ON_TWO])
			return (ray);
		ray->y_end = get_y_with_x(data, ray->x_end, pov);
		if (ray->y_end >= array_len((void **)data->map) || ray->y_end < 0)
			return (ray);
		if (ray->x_end >= data->precomputed->map_lines_len[(int)ray->y_end]
			|| ray->x_end < 0)
			return (ray);
		if (check_collision_x(data, ray, pov))
			ray->coll = true;
	}
	return (ray);
}

t_ray	*get_collision_coord(t_data *data, float pov)
{
	t_ray	*ray_horizontal;
	t_ray	*ray_vertical;


	ray_vertical = get_collision_x(data, pov);
	ray_horizontal = get_collision_y(data, pov);
	// if on big axis return before to avoid overflow
	ray_vertical->len = get_ray_len(data, ray_vertical);
	ray_horizontal->len = get_ray_len(data, ray_horizontal);
	if (!ray_horizontal->coll)
		return (ray_vertical);
	if (!ray_vertical->coll)
		return (ray_horizontal);
	if (ray_horizontal->len < ray_vertical->len)
	{
		free(ray_vertical);
		return (ray_horizontal);
	}
	free(ray_horizontal);
	return (ray_vertical);
}
