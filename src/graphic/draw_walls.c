/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:06:29 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/09 13:09:06 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_wall_pixel(t_data *data, t_ray *ray, float wall_height,
	int pixels[2])
{
	int	color;
	int	x;
	int	y;

	x = get_pixel_from_sprite_x(ray);
	y = get_pixel_from_sprite_y(data, wall_height, pixels[Y]);
	color = ft_get_color_from_texture(data->textures[ray->dir], x, y);
	my_mlx_pixel_put(data->image, pixels[0], pixels[1], color);
}

void	draw_stripe(t_data *data, float wall_height_coef, int stripe_index,
	t_ray *ray)
{
	float	wall_height;
	int		pixels[2];
	float	pixels_max[2];

	wall_height = wall_height_coef * WIN_HEIGHT;
	if (wall_height > WIN_HEIGHT)
		wall_height = WIN_HEIGHT;
	pixels[X] = stripe_index * data->precomputed->stripe;
	pixels[Y] = data->precomputed->float_line - (wall_height * 0.5);
	pixels_max[X] = stripe_index * data->precomputed->stripe
		+ data->precomputed->stripe + 1;
	pixels_max[Y] = data->precomputed->float_line + wall_height * 0.5;
	while (pixels[X] < pixels_max[X])
	{
		pixels[Y] = data->precomputed->float_line - (wall_height * 0.5);
		while (pixels[Y] < pixels_max[Y])
		{
			draw_wall_pixel(data, ray, wall_height, pixels);
			pixels[Y]++;
		}
		pixels[X]++;
	}
}

float	get_fov_angles(int i)
{
	float	fov_step_angle;
	float	fov_step_h;
	float	fov_step_v;

	fov_step_v = cos(30 * 0.0174533);
	fov_step_h = (2 * (i / (float)RAYS) - 1) * tan (30 * 0.0174533);
	fov_step_angle = atan(fov_step_h / fov_step_v);
	return (fov_step_angle);
}

void	draw_walls(t_data *data)
{
	t_ray	*ray;
	float	mid_ray;
	float	wall_height_coef;
	float	i;
	float	pov;

	i = 0;
	mid_ray = data->player->pov;
	pov = mid_ray + data->precomputed->fov_amplitude;
	while (i < RAYS)
	{
		if (pov < 0)
			pov += TWO_PI;
		if (pov > TWO_PI)
			pov -= TWO_PI;
		ray = get_collision_coord(data, pov);
		wall_height_coef = 1 / (get_ray_len(data, ray)
				* cos(fabs(pov - mid_ray)));
		draw_stripe(data, wall_height_coef, i, ray);
		pov = mid_ray - get_fov_angles(i);
		i++;
	}
}
