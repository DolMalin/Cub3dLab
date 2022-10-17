#include "../../includes/cub3d.h"

int	exit_program(t_data *data)
{
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
    free_data(data);
	exit(EXIT_SUCCESS);
}

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	print_bigger(t_image *image, int x, int y, int color_code)
{
	int i = 0;
	int j = 0;

	i = 0;
	while (i < COEF_MAP)
	{
		j = 0;
		while (j < COEF_MAP)
		{
			my_mlx_pixel_put(image, (x * COEF_MAP) + i + 20, (y * COEF_MAP) + j + 20, color_code);
			j++;
		}
		i++;
	}
}

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

int	get_events(int key, t_data *data)
{
	update_player_pos(&data);
	if (key == ESCAPE_KC)
		exit_program(data);
	move_player(data, key);
	return (0);
}

int	create_image(t_data *data)
{
	put_background_to_image(data);
	put_mini_map_to_image(data);
	return (0);
}

void	run_game(t_data *data)
{
	mlx_hook(data->mlx_win, 2, 0, get_events, data);
	mlx_loop_hook(data->mlx, create_image, data);
	mlx_hook(data->mlx_win, 17, 1L << 0, exit_program, &data);
	mlx_loop(data->mlx);
}
