/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:52:43 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/02 17:38:17 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	get_ray_len(t_data *data, t_ray *ray)
{

	float b;
	float c;
	float bcarre;
	float ccarre;
	
	b = ray->y_end - data->player->y;
	c = ray->x_end - data->player->x;
	bcarre = b * b;
	ccarre = c * c;
	return (
		sqrtf(bcarre + ccarre)
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
		i++;
	}
	data->player->pov = temp;
}


void	put_stripe_to_image(t_data *data, float wall_height_coef, int stripe_index, int wall_dir)
{
	float   wall_height;
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
		ray_len = get_ray_len(data, ray) * cos(fabs(data->player->pov - mid_ray));
		wall_height_coef = 1 / ray_len;
		put_stripe_to_image(data, wall_height_coef, i, ray->dir);
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
