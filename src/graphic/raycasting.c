/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:52:43 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/11 17:58:45 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	get_ray_len(float x_start, float x_end, float y_start, float y_end)
{
	return (
		sqrtf(((y_end - y_start) * (y_end - y_start))
			+ ((x_end - x_start) * (x_end - x_start)))
	);
}

int	get_pixel_from_sprite_y(t_data *data, float wall_height, int wall_cursor_y)
{
	int	pixel_y_sprite;
	int	temp;

	temp = wall_cursor_y - (data->precomputed->float_line - wall_height * 0.5);
	pixel_y_sprite = temp / wall_height * data->textures[NO]->width;
	return (pixel_y_sprite);
}

int	get_pixel_from_sprite_x(t_data *data, t_ray *ray)
{
	int		pixel_x_sprite;

	if (ray->dir == NO || ray->dir == SO)
		pixel_x_sprite = (ray->x_end - floor(ray->x_end))
			* data->textures[NO]->width;
	else
		pixel_x_sprite = (ray->y_end - floor(ray->y_end))
			* data->textures[NO]->width;
	return (pixel_x_sprite);
}

void	draw_rays(t_data *data)
{
	t_ray	*ray;
	float	mid_ray;
	float	pov;

	mid_ray = data->player->pov;
	pov = mid_ray + data->precomputed->fov_amplitude;
	ray = get_collision_coord(data, pov);
	draw_line(data, ray->x_end, ray->y_end);
}

void	raycasting(t_data *data)
{
	draw_walls(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->image->ptr, 0, 0);
}
