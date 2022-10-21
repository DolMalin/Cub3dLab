#include "../../includes/cub3d.h"

float	get_x_with_y(t_data *data, float next_y)
{
	float	next_x;

	next_x = ((next_y - data->player->y) / tan(data->player->pov)) + data->player->x;
	//printf("next_x %f\n", next_x);
	return (next_x);
}

float	get_y_with_x(t_data *data, float next_x)
{
	float	next_y;

	next_y = tan(data->player->pov) * (next_x - data->player->x) + data->player->y;
	//printf("next_y %f\n", next_y);
	return (next_y);
}


t_ray	*get_horizontal_collision(t_data *data)
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
		if (data->player->pov <= M_PI)
			ray->y_end = floor(ray->y_end - 1);
		if (data->player->pov > M_PI)
			ray->y_end = floor(ray->y_end + 1);
		ray->x_end = get_x_with_y(data, ray->y_end);
		if (ray->x_end > ft_strlen(data->map[(int)ray->y_end]) || ray->x_end < 0)
			return (ray);
		if (ray->y_end > array_len((void **)data->map) || ray->y_end < 0)
			return (ray);
		if (data->map[(int)ray->y_end][(int)ray->x_end] == '1')
		{
			ray->coll = true;
			break ;
		}
	}
	return (ray);
}

t_ray	*get_vertical_collision(t_data *data)
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
		if (data->player->pov <= M_PI_2 || data->player->pov >= 3 * M_PI_2)
			ray->x_end = floor(ray->x_end + 1);
		if (data->player->pov > M_PI_2 && data->player->pov < 3 * M_PI_2)
			ray->x_end = floor(ray->x_end - 1);
		ray->y_end = get_y_with_x(data, ray->x_end);
		if (ray->y_end > array_len((void **)data->map) || ray->y_end < 0)
			return (ray);
		if (ray->x_end > ft_strlen(data->map[(int)ray->y_end]) || ray->x_end < 0)
			return (ray);
		if (data->map[(int)floor(ray->y_end)][(int)ray->x_end] == '1')
		{
			ray->coll = true ;
			break ;
		}
	}
	return (ray);
}

float	get_ray_len(t_data *data, t_ray *ray)
{
	float	ray_len;

	ray_len = (ray->x_end - data->player->x) / cos(data->player->pov);
	return (ray_len);
}

t_ray	*get_collision_coord(t_data *data)
{
	t_ray	*ray_horizontal;
	t_ray	*ray_vertical;

	ray_vertical = get_vertical_collision(data);
	ray_horizontal = get_horizontal_collision(data);
	if (!ray_vertical->coll)
		return (ray_horizontal);
	if (!ray_horizontal->coll)
		return (ray_vertical);
	if (get_ray_len(data, ray_horizontal) <= get_ray_len(data, ray_vertical))
		return (ray_horizontal);
	else if (get_ray_len(data, ray_vertical) < get_ray_len(data, ray_horizontal))
		return (ray_vertical);
	return (NULL); // replace with 
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
		my_mlx_pixel_put(data->image, pixel_x * PRINT_COEF + 20, pixel_y * PRINT_COEF + 20, 0x0D062B);
		pixel_x += deltaX;
		pixel_y += deltaY;
		pixels--;
	}
}

void	draw_rays(t_data *data)
{
	float	fov_angle;
	fov_angle = -0.52;
	t_ray *ray = get_collision_coord(data);
	while (fov_angle < 0.52)
	{
		data->player->ray_coef_x = cos(data->player->pov + fov_angle);
		data->player->ray_coef_y = sin(data->player->pov + fov_angle);
		draw_line(data, ray->x_end , ray->y_end);
		fov_angle += 0.1;
	}
}

void    raycasting(t_data *data)
{
	t_ray *ray = get_collision_coord(data);


	draw_line(data, ray->x_end, ray->y_end);

	mlx_put_image_to_window(data->mlx, data->mlx_win, data->image->ptr, 0, 0);
}
