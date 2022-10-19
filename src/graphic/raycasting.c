#include "../../includes/cub3d.h"

void		draw_ray(t_data *data)
{
	int	ray_color;
	int	i;
	float	ray_x;
	float	ray_y;

	ray_color = 0x0D062B;
	i = 0;
	ray_x = data->player->x * PRINT_COEF;
	ray_y = data->player->y * PRINT_COEF;
	while (i < 50)
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

void    raycasting(t_data *data)
{
    draw_rays(data);
}

