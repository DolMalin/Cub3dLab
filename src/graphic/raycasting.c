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

void    dda(t_data *data, float x_end, float y_end)
{	
	int	i;
    float step;
    float x;
    float y;

    if (fabs(x_end - data->player->x) > fabs(y_end - data->player->y))
        step = fabs(x_end - data->player->x);
    else
        step = fabs(y_end - data->player->y);
    x = data->player->x * PRINT_COEF + 20;
    y = data->player->y * PRINT_COEF + 20;
    i = 0;
    while(i < step)
    {
        my_mlx_pixel_put(data->image, x, y, 0x0D062B);
        x = x + ((x_end - data->player->x) / step);
        y = y + ((y_end - data->player->y) / step);
        i++;
    }
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->image->ptr, 0, 0);
}

get_wall_y()
get_wall_x()

void    raycasting(t_data *data)
{
    // draw_ray(data);
    
    dda(data, data->player->x - 50, data->player->y - 50);
    dda(data, get_wall_y(), get_wall_x());
}