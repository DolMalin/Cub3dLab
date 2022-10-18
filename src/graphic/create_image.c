#include "../../includes/cub3d.h"

static void	put_mini_map_to_image(t_data *data)
{
	int i = 0;
	int j = 0;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				print_bigger(data->image, j, i, 0x34A145);
			if (is_in_charset(data->map[i][j], "NSEW"))
				print_bigger(data->image, j, i, 0x6C207D);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->image->ptr, 0, 0);
	// what to free ?
}

void put_background_to_image(t_data *data)
{
	int		i;
	int		j;
	
	i = 0;
	while(i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			if (i / (WIN_HEIGHT * 0.5) <= 1)
				my_mlx_pixel_put(data->image, j, i, 0x352F24);
			 // replace by data->colors[CEIL]. need to convert RGB format with adding A in front in hexadecimal format
			if (i / (WIN_HEIGHT * 0.5) > 1)
				my_mlx_pixel_put(data->image, j, i, 0x822E18);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->image->ptr, 0, 0);
}

int	create_image(t_data *data)
{
	put_background_to_image(data);
	put_mini_map_to_image(data);
	return (0);
}