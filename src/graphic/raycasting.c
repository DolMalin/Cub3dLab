/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:52:43 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/04 15:30:25 by aandric          ###   ########lyon.fr   */
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

void	draw_rays(t_data *data)
{
	t_ray	*ray;
	float	temp;
	float	i;

	temp = data->player->pov;
	i = 0;
	data->player->pov += FOV_AMPLITUDE;
	while (i < FOV)
	{
		data->player->pov -= FOV_STEP;
		if (data->player->pov < 0)
			data->player->pov += 2 * M_PI;
		if (data->player->pov > 2 * M_PI)
			data->player->pov -= (2 * M_PI);
		ray = get_collision_coord(data);
		draw_line(data, ray->x_end, ray->y_end);
		free(ray);
		i++;
	}
	data->player->pov = temp;
}

int	get_pixel_from_sprite_y(float wall_height, int wall_cursor_y)
{
	int	pixel_y_sprite;

	// pixel_y_sprite = wall_height / SPRITE_SIZE * wall_cursor_y;
	pixel_y_sprite = (wall_cursor_y - (FLOAT_LINE - wall_height / 2)) / wall_height * SPRITE_SIZE;
	// printf("ratio pixel y : %f\n", (wall_cursor_y - (FLOAT_LINE - wall_height / 2)));
	return (pixel_y_sprite);
}

int	get_pixel_from_sprite_x(t_data *data)
{
	t_ray	*ray;
	int		pixel_x_sprite;

	ray = get_collision_coord(data);

	if (ray->dir == NO || ray->dir == SO)
		pixel_x_sprite = (ray->x_end - floor(ray->x_end)) * SPRITE_SIZE; // attention si valur deja ronde pour ray->x_end floor en dessous voir si mieux dutiliser cast (int)
	else
		pixel_x_sprite = (ray->y_end - floor(ray->y_end)) * SPRITE_SIZE; 
	free(ray);
	return (pixel_x_sprite);
}

int ft_get_color_from_texture(t_texture *texture, int x, int y)
{
    return (*(int *)(texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8))));
}

void	put_stripe_to_image(t_data *data, float wall_height_coef,
		int stripe_index, int wall_dir)
{
	float	wall_height;
	int		pixel_x;
	int		pixel_y;
	int		color;

	if (wall_dir == NO)
		color = 0xff0000;
	if (wall_dir == SO)
		color = 0xad0000;
	if (wall_dir == WE)
		color = 0x820000;
	if (wall_dir == EA)
		color = 0x450000;

	wall_height = wall_height_coef * WIN_HEIGHT;
	if (wall_height > WIN_HEIGHT)
		wall_height = WIN_HEIGHT;
	pixel_x = stripe_index * STRIPE;
	pixel_y = FLOAT_LINE - wall_height / 2;
	while (pixel_x < stripe_index * STRIPE + STRIPE + 1)
	{
		pixel_y = FLOAT_LINE - wall_height / 2;
		while (pixel_y < FLOAT_LINE + wall_height / 2)
		{
			color = ft_get_color_from_texture(data->textures[wall_dir], get_pixel_from_sprite_x(data), get_pixel_from_sprite_y(wall_height, pixel_y));
			my_mlx_pixel_put(data->image, pixel_x, pixel_y, color);
			pixel_y++;
		}
		pixel_x++;
	}
}

void	get_wall_height(t_data *data)
{
	t_ray	*ray;
	float	mid_ray;
	float	wall_height_coef;
	float	ray_len;
	float	i;

	i = 0;
	mid_ray = data->player->pov;
	data->player->pov += FOV_AMPLITUDE;
	while (i < FOV)
	{
		if (data->player->pov < 0)
			data->player->pov += 2 * M_PI;
		if (data->player->pov > 2 * M_PI)
			data->player->pov -= (2 * M_PI);
		ray = get_collision_coord(data);
		ray_len = get_ray_len(data, ray)
			* cos(fabs(data->player->pov - mid_ray));
		wall_height_coef = 1 / ray_len;
		put_stripe_to_image(data, wall_height_coef, i, ray->dir);
		free(ray);
		data->player->pov -= FOV_STEP;
		i++;
	}
	data->player->pov = mid_ray;
}

void	raycasting(t_data *data)
{
	get_wall_height(data);
	draw_rays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->image->ptr, 0, 0);
}
