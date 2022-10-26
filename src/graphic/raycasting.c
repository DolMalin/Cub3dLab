/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:52:43 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/10/26 13:12:37 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	get_ray_len(t_data *data, t_ray *ray)
{
	return (
		sqrtf((ray->y_end - data->player->y) * (ray->y_end - data->player->y))
		+ (ray->x_end - data->player->x) * (ray->x_end - data->player->x)
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
		if (data->player->pov <= 0)
			data->player->pov += 2 * M_PI;
		if (data->player->pov >= 2 * M_PI)
			data->player->pov -= (2 * M_PI);
		ray = get_collision_coord(data);
		draw_line(data, ray->x_end, ray->y_end);
		i++;
	}
	data->player->pov = temp;
}

void	put_stripe_to_image(t_data *data, float wall_height_coef, int stripe_index)
{
	int		pixel_x;
	int		pixel_y;
	
	pixel_x = stripe_index * STRIPE;
	pixel_y = 0;
	
	while (pixel_x < stripe_index * STRIPE + stripe_index)
	{
		while (pixel_y < wall_height_coef * WIN_HEIGHT)
		//while (pixel_y < WIN_HEIGHT)
		{
			my_mlx_pixel_put(data->image, pixel_x, (pixel_y + wall_height_coef * WIN_HEIGHT / 2), 0xfffff);
			pixel_y++;
		}
		pixel_x++;
	}
}

void	get_wall_height(t_data *data)
{
	t_ray	*ray;
	float	temp;
	float	wall_height_coef;
	float	i;

	temp = data->player->pov;
	i = 0;
	data->player->pov += FOV_AMPLITUDE;
	while (i < FOV)
	{
		data->player->pov -= FOV_STEP;
		if (data->player->pov <= 0)
			data->player->pov += 2 * M_PI;
		if (data->player->pov >= 2 * M_PI)
			data->player->pov -= (2 * M_PI);
		ray = get_collision_coord(data);
		wall_height_coef = 1 / get_ray_len(data, ray);
		//printf("wall height coef : %f\n", wall_height_coef);
		put_stripe_to_image(data, wall_height_coef, i);
		i++;
	}
	data->player->pov = temp;
}

void	raycasting(t_data *data)
{
	// get_wall_height(data);
	draw_rays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->image->ptr, 0, 0);
}
