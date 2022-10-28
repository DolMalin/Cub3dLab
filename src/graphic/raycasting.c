/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:52:43 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/10/28 16:37:19 by aandric          ###   ########lyon.fr   */
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
	float   wall_height;
	int		pixel_x;
	int		pixel_y;
	
	wall_height = wall_height_coef * WIN_HEIGHT;
	// if (wall_height > WIN_HEIGHT)
	// 	wall_height = WIN_HEIGHT;
	pixel_x = stripe_index * STRIPE;
	pixel_y = FLOAT_LINE - wall_height / 2;

	while (pixel_x < stripe_index * STRIPE + STRIPE + 1)
	{
		pixel_y = FLOAT_LINE - wall_height / 2;
		while (pixel_y < FLOAT_LINE + wall_height)
		{
			my_mlx_pixel_put(data->image, pixel_x, pixel_y, 0xfffff);
			pixel_y++;
		}
		pixel_x++;
	}
}

// void	get_wall_height(t_data *data)
// {
// 	t_ray	*ray;
// 	float	temp;
// 	float	wall_height_coef;
// 	float	ray_len;
// 	float	fov_angle;
// 	float	i;

// 	temp = data->player->pov;
// 	i = 0;
// 	data->player->pov += FOV_AMPLITUDE;
// 	while (i < FOV)
// 	{
// 		data->player->pov -= FOV_STEP;
// 		if (data->player->pov < 0)
// 			data->player->pov += 2 * M_PI;
// 		if (data->player->pov > 2 * M_PI)
// 			data->player->pov -= (2 * M_PI);
// 		ray = get_collision_coord(data);
// 		ray_len = get_ray_len(data, ray);
// 		fov_angle = temp - data->player->pov;
// 		// fov_angle = (FOV - i) / 2 * FOV_STEP;
// 		if (fov_angle < 0)
// 			fov_angle += 2 * M_PI;
// 		if (fov_angle > 2 * M_PI)
// 			fov_angle -= 2 * M_PI;
// 		// 	printf("player angle %f\n pov angle %f\n", temp, data->player->pov);
// 		// printf("fov_angle %f\n", fov_angle);
// 		// printf("ray_len before : %f\n", ray_len);
// 		// float delta_y = ray->y_end - data->y;
// 		// if ((data->player->pov > (3 * M_PI_4) && data->player->pov < (5 * M_PI_4)) || data->player->pov > (7 * M_PI_4) || data->player->pov < M_PI_4)
// 		//ray_len = ray_len * cos(fov_angle);
// 		//else
// 		//ray_len = ray_len * cos(M_PI_2 - fov_angle);
// 		ray_len = ray_len + (2 * tan(FOV / 2) / FOV);
// 		// ray_len = ray_len - (2 * tan(FOV / 2) / FOV);
// 		// ray_len = ray_len + delta_y;
// 		// printf("ray_len after : %f\n", ray_len);
// 		wall_height_coef = 1 / ray_len;
// 		// printf("wall height coef : %f\n", wall_height_coef);
// 		put_stripe_to_image(data, wall_height_coef, i);
// 		i++;
// 	}
// 	data->player->pov = temp;
// }

void	get_wall_height(t_data *data)
{
	t_ray	*ray;
	float	temp;
	float	wall_height_coef;
	float	ray_len;
	float	fov_angle;
	float	i;

	temp = data->player->pov;
	i = 0;
	data->player->pov += FOV_AMPLITUDE;
	// if (data->player->pov > 2 * M_PI)
	// 	data->player->pov -= 2 * M_PI;
	// 	if (data->player->pov < 0)
	// 	data->player->pov += 2 * M_PI;
	while (i < FOV)
	{
		if (data->player->pov < 0)
			data->player->pov += 2 * M_PI;
		if (data->player->pov > 2 * M_PI)
			data->player->pov -= (2 * M_PI);
		ray = get_collision_coord(data);
		ray_len = get_ray_len(data, ray);
		fov_angle = data->player->pov - temp;
		if (fov_angle < 0)
			fov_angle += 2 * M_PI;
		if (fov_angle > 2 * M_PI)
			fov_angle -= 2 * M_PI;
		printf("ray_len before : %f\n", ray_len);
		ray_len = ray_len * cos(fabs(fov_angle));
		printf("ray_len after : %f\n", ray_len);
		//ray_len = ray_len + (2 * tan(FOV / 2) / FOV);
		wall_height_coef = 1 / ray_len;
		data->player->pov -= FOV_STEP;
		put_stripe_to_image(data, wall_height_coef, i);
		i++;
	}
	data->player->pov = temp;
}

void	raycasting(t_data *data)
{
	get_wall_height(data);
	draw_rays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->image->ptr, 0, 0);
}
