/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:00:31 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/03 11:55:52 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_bool	check_collision_y(t_data *data, t_ray *ray)
{
	if (ray->y_end == 0 || ray->y_end == array_len((void **)data->map))
		return (true);
	if (data->player->pov > 0 && data->player->pov <= M_PI_2)
		if (data->map[(int)(ray->y_end - 1)][(int)floor(ray->x_end)] == '1')
			return (true);
	if (data->player->pov >= M_PI_2 && data->player->pov < M_PI)
		if (data->map[(int)(ray->y_end - 1)][(int)floor(ray->x_end)] == '1')
			return (true);
	if (data->player->pov > M_PI && data->player->pov <= 3 * M_PI_2)
		if (data->map[(int)(ray->y_end)][(int)floor(ray->x_end)] == '1')
			return (true);
	if (data->player->pov > 3 * M_PI_2)
		if (data->map[(int)(ray->y_end)][(int)floor(ray->x_end)] == '1')
			return (true);
	return (false);
}

static t_bool	check_collision_x(t_data *data, t_ray *ray)
{
	if (data->player->pov == 0 || data->player->pov == M_PI)
		if (data->map[(int)ray->y_end][(int)ray->x_end] == '1')
			return (true);
	if (ray->x_end == 0 || ray->x_end
		== ft_strlen(data->map[(int)floor(ray->y_end)]))
		return (true);
	if (data->player->pov >= 0 && data->player->pov <= M_PI_2)
		if (data->map[(int)floor(ray->y_end)][(int)(ray->x_end)] == '1')
			return (true);
	if (data->player->pov > M_PI_2 && data->player->pov <= M_PI)
		if (data->map[(int)floor(ray->y_end)][(int)(ray->x_end - 1)] == '1')
			return (true);
	if (data->player->pov >= M_PI && data->player->pov <= 3 * M_PI_2)
		if (data->map[(int)floor(ray->y_end)][(int)(ray->x_end - 1)] == '1')
			return (true);
	if (data->player->pov > 3 * M_PI_2)
		if (data->map[(int)floor(ray->y_end)][(int)(ray->x_end)] == '1')
			return (true);
	return (false);
}

static t_ray	*get_collision_y(t_data *data)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->x_end = 1000000;
	ray->y_end = data->player->y;
	ray->angle = data->player->pov;
	ray->coll = false;
	while (!ray->coll)
	{
		ray->y_end = get_fixed_ray_end(data, ray, 'y');
		ray->dir = get_wall_dir(data, ray, 'y');
		if (data->player->pov == M_PI || data->player->pov == 0)
			return (ray);
		ray->x_end = get_x_with_y(data, ray->y_end);
		if (ray->x_end >= ft_strlen(data->map[(int)ray->y_end])
			|| ray->x_end < 0)
			return (ray);
		if (ray->y_end > array_len((void **)data->map) || ray->y_end < 0)
			return (ray);
		if (check_collision_y(data, ray))
			ray->coll = true;
	}
	return (ray);
}

static t_ray	*get_collision_x(t_data *data)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->x_end = data->player->x;
	ray->y_end = 1000000;
	ray->angle = data->player->pov;
	ray->coll = false;
	while (!ray->coll)
	{
		ray->x_end = get_fixed_ray_end(data, ray, 'x');
		ray->dir = get_wall_dir(data, ray, 'x');
		if (data->player->pov == M_PI_2 || data->player->pov == 3 * M_PI_2)
			return (ray);
		ray->y_end = get_y_with_x(data, ray->x_end);
		if (ray->y_end >= array_len((void **)data->map) || ray->y_end < 0)
			return (ray);
		if (ray->x_end >= ft_strlen(data->map[(int)ray->y_end])
			|| ray->x_end < 0)
			return (ray);
		if (check_collision_x(data, ray))
			ray->coll = true;
	}
	return (ray);
}

t_ray	*get_collision_coord(t_data *data)
{
	t_ray	*ray_horizontal;
	t_ray	*ray_vertical;

	ray_vertical = get_collision_x(data);
	ray_horizontal = get_collision_y(data);
	if (!ray_vertical->coll)
		return (ray_horizontal);
	if (!ray_horizontal->coll)
		return (ray_vertical);
	ray_vertical->len = get_ray_len(data, ray_vertical);
	ray_horizontal->len = get_ray_len(data, ray_horizontal);
	if (ray_horizontal->len >= ray_vertical->len)
		return (ray_vertical);
	if (ray_horizontal->len < ray_vertical->len)
		return (ray_horizontal);
	return (NULL);
}
