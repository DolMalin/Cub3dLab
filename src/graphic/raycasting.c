#include "../../includes/cub3d.h"

float	get_y_with_x(t_data *data, float next_x)
{
	float	next_y;

	next_y = tan(data->player->pov) * (data->player->x - next_x) + data->player->y;
	return (next_y);
}

float	get_x_with_y(t_data *data, float next_y)
{
	float	next_x;

	next_x = (data->player->y - next_y) / tan(data->player->pov) + data->player->x;  
	return (next_x);
}

t_ray	*get_collision_y(t_data *data)
{
	t_ray	*ray;
	
	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->x_end = 9999999;
	ray->y_end = data->player->y;
	ray->angle = data->player->pov;
	ray->coll = false;
	while (!ray->coll)
	{
		if (data->player->pov <= M_PI) // looking down
			ray->y_end = floor(ray->y_end - 1);
		else
			ray->y_end = floor(ray->y_end + 1); // looking up
		ray->x_end = get_x_with_y(data, ray->y_end);
		if (ray->x_end >= ft_strlen(data->map[(int)ray->y_end]) || ray->x_end <= 0)
			return (ray);
		if (ray->y_end >= array_len((void **)data->map) || ray->y_end <= 0)
			return (ray);
		if (data->player->pov > 0 && data->player->pov <= M_PI_2) // NE
			if (data->map[(int)(ray->y_end - 1)][(int)floor(ray->x_end)] == '1')
				ray->coll = true;
		if (data->player->pov > M_PI_2 && data->player->pov <= M_PI) // NO
			if (data->map[(int)(ray->y_end - 1)][(int)floor(ray->x_end)] == '1')
				ray->coll = true;
		if (data->player->pov > M_PI && data->player->pov <= 3 * M_PI_2) // SO
			if (data->map[(int)(ray->y_end)][(int)floor(ray->x_end)] == '1')
				ray->coll = true;
		if (data->player->pov > 3 * M_PI_2) // SE
			if (data->map[(int)(ray->y_end)][(int)floor(ray->x_end)] == '1')
				ray->coll = true;
	}
	return (ray);
}
t_ray	*get_collision_x(t_data *data)
{
	t_ray	*ray;
	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->x_end = data->player->x;
	ray->y_end = 999999999;
	ray->angle = data->player->pov;
	ray->coll = false;

	while (!ray->coll)
	{
		if (data->player->pov <= M_PI_2 || data->player->pov >= 3 * M_PI_2) // looking right
			ray->x_end = floor(ray->x_end + 1);
		else
			ray->x_end = floor(ray->x_end - 1); // looking left
		ray->y_end = get_y_with_x(data, ray->x_end);
		if (ray->y_end >= array_len((void **)data->map) || ray->y_end <= 0)
			return (ray);
		if (ray->x_end >= ft_strlen(data->map[(int)ray->y_end]) || ray->x_end <= 0)
			return (ray);
		if (data->player->pov > 0 && data->player->pov <= M_PI_2) // NE
			if (data->map[(int)floor(ray->y_end)][(int)(ray->x_end)] == '1')
				ray->coll = true;
		if (data->player->pov > M_PI_2 && data->player->pov <= M_PI) // NO
			if (data->map[(int)floor(ray->y_end)][(int)(ray->x_end - 1)] == '1')
				ray->coll = true;
		if (data->player->pov > M_PI && data->player->pov <= 3 * M_PI_2) // SE
			if (data->map[(int)floor(ray->y_end)][(int)(ray->x_end - 1)] == '1')
				ray->coll = true;
		if (data->player->pov > 3 * M_PI_2) // SO
			if (data->map[(int)floor(ray->y_end)][(int)(ray->x_end)] == '1')
				ray->coll = true;
	}
	return (ray);
}
float	get_ray_len(t_data *data, t_ray *ray)
{
	return (sqrtf((ray->y_end - data->player->y) * (ray->y_end - data->player->y)) 
		+ (ray->x_end - data->player->x) * (ray->x_end - data->player->x));
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
	
	if (get_ray_len(data, ray_horizontal) >= get_ray_len(data, ray_vertical))
	{
	//	printf("ray len horizontal %f ray len vertical %f\n", get_ray_len(data, ray_horizontal), get_ray_len(data, ray_vertical));
		return (ray_vertical);
	}
	if (get_ray_len(data, ray_horizontal) < get_ray_len(data, ray_vertical))
	{
	//	printf("ray len horizontal %f ray len vertical %f\n", get_ray_len(data, ray_horizontal), get_ray_len(data, ray_vertical));
		return (ray_horizontal);
	}
	return (NULL);
}
void	draw_line(t_data *data, float end_x, float end_y)
{
	float	deltaX;
	float	deltaY;
	int		pixels;
	float	pixel_x;
	float	pixel_y;
	deltaX = end_x - data->player->x;
	deltaY = end_y - data->player->y;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY)) * PRINT_COEF + 20;
	deltaX = deltaX / pixels;
	deltaY = deltaY / pixels;
	pixel_x = data->player->x;
	pixel_y = data->player->y;
	while(pixels)
	{
		if (pixels == 1)
			my_mlx_pixel_put(data->image, pixel_x * PRINT_COEF + 20, pixel_y * PRINT_COEF + 20, 0xfffff);
		else	
			my_mlx_pixel_put(data->image, pixel_x * PRINT_COEF + 20, pixel_y * PRINT_COEF + 20, 0x0D062B);
		pixel_x += deltaX;
		pixel_y += deltaY;
		pixels--;
	}
}
void	draw_rays(t_data *data)
{
	t_ray	*ray;
	float	temp;
	//float	fov_angle;
	float	i;

	temp = data->player->pov;
	i = 0;
	data->player->pov -= FOV_AMPLITUDE;
	while (i < FOV)
	{
		data->player->pov += FOV_STEP;
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
void    raycasting(t_data *data)
{
	//t_ray *ray = get_collision_coord(data);
	//printf("ray_x = %f, ray_y = %f, ray_len = %f\n", ray->x_end, ray->y_end, get_ray_len(data, ray));
	//draw_line(data, ray->x_end, ray->y_end);
	draw_rays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->image->ptr, 0, 0);
}