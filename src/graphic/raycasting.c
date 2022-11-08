/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:52:43 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/08 12:01:32 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	get_ray_len(t_data *data, t_ray *ray)
{
	return (
		sqrtf(((ray->y_end - data->player->y) * (ray->y_end - data->player->y))
			+ ((ray->x_end - data->player->x) * (ray->x_end - data->player->x)))
	);
}



int	get_pixel_from_sprite_y(t_data *data, float wall_height, int wall_cursor_y)
{
	int	pixel_y_sprite;

	pixel_y_sprite = (wall_cursor_y - (data->precomputed->float_line - wall_height * 0.5)) / wall_height * SPRITE_SIZE;
	return (pixel_y_sprite);
}

int	get_pixel_from_sprite_x(t_data *data, float pov)
{
	t_ray	*ray;
	int		pixel_x_sprite;

	ray = get_collision_coord(data, pov);
	if (ray->dir == NO || ray->dir == SO)
		pixel_x_sprite = (ray->x_end - floor(ray->x_end)) * SPRITE_SIZE;
	else
		pixel_x_sprite = (ray->y_end - floor(ray->y_end)) * SPRITE_SIZE; 
	// free(ray);
	return (pixel_x_sprite);
}

int ft_get_color_from_texture(t_texture *texture, int x, int y)
{
    return (*(int *)(texture->addr + (y * texture->line_length + x * texture->bits_per_pixel / 8)));
}

void	put_stripe_to_image(t_data *data, float wall_height_coef,
		int stripe_index, int wall_dir, float pov)
{
	float	wall_height;
	int		pixel_x;
	int		pixel_y;
	int		color;
	int		x_y_max[2];
	
	wall_height = wall_height_coef * WIN_HEIGHT;
	if (wall_height > WIN_HEIGHT)
		wall_height = WIN_HEIGHT;
	pixel_x = stripe_index * data->precomputed->stripe;
	pixel_y = data->precomputed->float_line - (wall_height * 0.5);
	x_y_max[0] = stripe_index * data->precomputed->stripe + data->precomputed->stripe + 1;
	x_y_max[1] = data->precomputed->float_line + wall_height * 0.5;
	while (pixel_x < x_y_max[0])
	{
		pixel_y = data->precomputed->float_line - (wall_height * 0.5);
		while (pixel_y < x_y_max[1])
		{
			// if (pixel_y % 2 == 0 )
				color = ft_get_color_from_texture(data->textures[wall_dir],
					get_pixel_from_sprite_x(data, pov), 
					get_pixel_from_sprite_y(data, wall_height, pixel_y));
			my_mlx_pixel_put(data->image, pixel_x, pixel_y, color);
			pixel_y++;
		}
		pixel_x++;
	}
}

float	get_fov_angles(int i)
{
	float fov_step_angle;
	float fov_step_h;
	float fov_step_v;
	
	fov_step_v = cos(30 * 0.0174533);
	fov_step_h = (2 * (i / (float)RAYS) - 1) * tan (30 * 0.0174533);
	fov_step_angle = atan(fov_step_h / fov_step_v);
	return (fov_step_angle);
}

void	draw_rays(t_data *data)
{
	t_ray	*ray;
	float	mid_ray;
	// float	i;
	float	pov;

	// i = 0;
	mid_ray = data->player->pov;
	pov = mid_ray + data->precomputed->fov_amplitude;
	// while (i < RAYS)
	// {
	// 	if (pov < 0)
	// 		pov += TWO_PI;
	// 	if (pov > TWO_PI)
	// 		pov -= TWO_PI;
		ray = get_collision_coord(data, pov);
		draw_line(data, ray->x_end, ray->y_end);
	// 	// pov -= FOV_STEP;
	// 	pov = mid_ray - get_fov_angles(i);
	// 	i++;
	// }
}
// {
// 	t_ray	*ray;
// 	float	temp;
// 	float	i;

// 	temp = data->player->pov;
// 	i = 0;
// 	data->player->pov += data->precomputed->fov_amplitude;
// 	while (i < RAYS)
// 	{
// 		data->player->pov -= get_fov_angles(i);
// 		if (data->player->pov < 0)
// 			data->player->pov += TWO_PI;
// 		if (data->player->pov > TWO_PI)
// 			data->player->pov -= TWO_PI;
// 		ray = get_collision_coord(data, data->player->pov);
// 		draw_line(data, ray->x_end, ray->y_end);
// 		free(ray);
// 		i++;
// 	}
// 	data->player->pov = temp;

	
// }

void	get_wall_height(t_data *data)
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
		wall_height_coef = 1 / (get_ray_len(data, ray) * cos(fabs(pov - mid_ray)));
		put_stripe_to_image(data, wall_height_coef, i, ray->dir, pov);
		// pov -= FOV_STEP;
		pov = mid_ray - get_fov_angles(i);
		i++;
	}
}

void	raycasting(t_data *data)
{
	get_wall_height(data);
	draw_rays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->image->ptr, 0, 0);
}
