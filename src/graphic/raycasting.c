#include "../../includes/cub3d.h"

float	get_x_with_y(t_data *data, float next_y)
{
	float	next_x;

	next_x = ((next_y - data->player->y) / tan(data->player->pov)) + data->player->x;
	return (next_x);
}

float	get_y_with_x(t_data *data, float next_x)
{
	float	next_y;

	next_y = tan(data->player->pov) * (next_x - data->player->x) + data->player->y;
	return (next_y);
}

t_ray	get_vertical_collision(t_data *data)
{
	t_ray	ray;

	ray.x_start = data->player->x;
	ray.y_start = data->player->y;
	ray.x_end = 9999999;
	ray.y_end = data->player->y;
	ray.angle = data->player->pov;
	ray.coll = false;
	while (!ray.coll)
	{
		if (data->player->pov <= M_PI)
			ray.y_end = floor(ray.y_end - 1);
		if (data->player->pov > M_PI)
			ray.y_end = floor(ray.y_end + 1);
		ray.x_end = floor(get_x_with_y(data, ray.y_end));
		if (ray.x_end > ft_strlen(data->map[(int)ray.y_end]))
			return (ray) ;
		printf("x = %f\n", ray.x_start);
		printf("x_end = %f\n", ray.x_end);
		printf("y_end = %f\n", ray.y_end);
		if (data->map[(int)ray.y_end][(int)ray.x_end] == '1')
			ray.coll = true;
	}
	printf("la\n");
	return (ray);
}

t_ray	get_horizontal_collision(t_data *data)
{
	t_ray	ray;

	ray.x_start = data->player->x;
	ray.y_start = data->player->y;
	ray.x_end = data->player->x;
	ray.y_end = 999999999;
	ray.angle = data->player->pov;
	ray.coll = false;
	while (!ray.coll)
	{
		if (data->player->pov <= M_PI_2 || data->player->pov >= 3 * M_PI_2)
			ray.x_end = floor(ray.x_end + 1);
		if (data->player->pov > M_PI_2 && data->player->pov < 3 * M_PI_2)
			ray.x_end = floor(ray.x_end - 1);
		ray.y_end = floor(get_y_with_x(data, ray.x_end));
		if (ray.y_end > array_len((void **)data->map)) // replace with end map
			return (ray);
		// printf("x = %f\n", ray.x_start);
		// printf("x_end = %f\n", ray.x_end);
		// printf("y_end = %f\n", ray.y_end);
		if (data->map[(int)ray.y_end][(int)ray.x_end] == '1')
		{
			ray.coll = true ;
			break ;
		}
	}
	return (ray);
}

float	get_ray_len(t_ray ray)
{
	float	ray_len;

	ray_len = (ray.x_end - ray.x_start) / cos(ray.angle);
	return (ray_len);
}

t_ray	get_collision_coord(t_data *data)
{
	t_ray	ray_horizontal;
	t_ray	ray_vertical;

	ray_vertical =  get_vertical_collision(data);
	ray_horizontal = get_horizontal_collision(data);
	printf(" ");
	if (!ray_vertical.coll)
		return (ray_horizontal);
	if (!ray_horizontal.coll)
		return (ray_vertical);
	if (get_ray_len(ray_horizontal) < get_ray_len(ray_vertical))
		return (ray_horizontal);
	else if (get_ray_len(ray_vertical) < get_ray_len(ray_horizontal))
		return (ray_vertical);

}

void		draw_ray(t_data *data)
{
	int	ray_color;
	int	i;
	float	ray_x;
	float	ray_y;
	t_ray	ray;

	ray_color = 0x0D062B;
	i = 0;
	ray = get_collision_coord(data);
	ray_x = data->player->x * PRINT_COEF;
	ray_y = data->player->y * PRINT_COEF;
	printf("x_end = %f\n", ray.x_end);
	printf("y_end = %f\n", ray.y_end);
	while (ray_x > (ray.x_end - 2) && ray_y > (ray.y_end - 2))
	{
		ray_x = ray_x - data->player->ray_coef_x;
		ray_y = ray_y - data->player->ray_coef_y;
		my_mlx_pixel_put(data->image, ray_x + 20, ray_y + 20, ray_color);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->image->ptr, 0, 0);
}

void	draw_rays(t_data *data)
{
	float	fov_angle;
	fov_angle = -0.52;
	while (fov_angle < 0.52)
	{
		data->player->ray_coef_x = cos(data->player->pov + fov_angle);
		data->player->ray_coef_y = sin(data->player->pov + fov_angle);
		draw_ray(data);
		fov_angle += 0.1;
	}
}

// void    dda(t_data *data, float x_end, float y_end)
// {	
// 	int	i;
//     float step;
//     float x;
//     float y;

//     if (fabs(x_end - data->player->x) > fabs(y_end - data->player->y))
//         step = fabs(x_end - data->player->x);
//     else
//         step = fabs(y_end - data->player->y);
//     x = data->player->x * PRINT_COEF + 20;
//     y = data->player->y * PRINT_COEF + 20;
//     i = 0;
//     while(i < step)
//     {
//         my_mlx_pixel_put(data->image, x, y, 0x0D062B);
//         x = x + ((x_end - data->player->x) / step);
//         y = y + ((y_end - data->player->y) / step);
//         i++;
//     }
//     mlx_put_image_to_window(data->mlx, data->mlx_win, data->image->ptr, 0, 0);
// }

// get_wall_y()
// get_wall_x()

void    raycasting(t_data *data)
{
    draw_rays(data);
    //dda(data, data->player->x - 50, data->player->y - 50);
    //dda(data, get_wall_y(), get_wall_x());
}
