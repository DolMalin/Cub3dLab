#include "../../includes/cub3d.h"

int	exit_program(t_data *data)
{
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
    free_data(data);
	exit(EXIT_SUCCESS);
}

typedef struct	s_image {
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


t_image	create_image(t_data *data)
{
	t_image	image;

	image.ptr = mlx_new_image(data->mlx, 1920, 1080);
	image.addr =mlx_get_data_addr(image.ptr, &image.bits_per_pixel, &image.line_length, &image.endian);
	return (image);
}

void	print_bigger(t_image *image, int x, int y, int color_code)
{
	int i = 0;
	int j = 0;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			my_mlx_pixel_put(image, x + i, y + j, color_code);
			j++;
		}
		i++;
	}
}

void	draw_square(t_data *data)
{
	int i = 0;
	int j = 0;
	int	band;
	int	bigger;

	i = 0;
	t_image image = create_image(data);
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
			{
				//print_bigger(&image, j, i, 0x0000ff00);
				band = 10;
				bigger = 0;
				while (bigger < band)
				{
					my_mlx_pixel_put(&image, (j * band) + bigger, (i * band) + bigger, 0x0000ff00);
					bigger++;
				}
			}
			if (is_in_charset(data->map[i][j], "NSEW"))
			{	
				band = 10;
				bigger = 0;
				while (bigger < band)
				{
					my_mlx_pixel_put(&image, (j * band) + bigger, (i * band) + bigger, 0x00ff00ff);
					bigger++;
				}
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, image.ptr, 20, 20);
}


int	get_events(int key, t_data *data)
{
	update_player_pos(&data);
	if (key == KB_W)
		move_up(&data);
	else if (key == KB_A)
		move_left(&data);
	else if (key == KB_D)
		move_right(&data);
	else if (key == KB_S)
		move_down(&data);
	else if (key == KB_LEFT)
		printf("ROTATE LEFT\n");
	else if (key == KB_RIGHT)
		printf("ROTATE RIGHT\n");
	else if (key == ESCAPE_KC)
		exit_program(data);
    print_map(data->map);
    printf("x = %d, y = %d\n", data->x, data->y);
	//draw_square(data);
	return (0);
}

void	run_game(t_data *data)
{
	//put_img(data, img, &data->mlx, &data->mlx_win);
	draw_square(data);
	mlx_hook(data->mlx_win, 2, 0, get_events, data);
	// mlx_hook(data->mlx_win, 17, 0, exit_program, data);
	mlx_hook(data->mlx_win, 17, 1L << 0, exit_program, &data);
	mlx_loop(data->mlx);
}
