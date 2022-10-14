#include "../../includes/cub3d.h"

int	exit_program(t_data *data)
{
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
    free_data(data);
	exit(EXIT_SUCCESS);
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
	return (0);
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

t_image	*create_image(t_data *data)
{
	t_image	*image;

	image = malloc(sizeof(image));
	if (!image)
		return (NULL);
	image->ptr = mlx_new_image(data->mlx, 1920, 1080);
	image->addr =mlx_get_data_addr(image->ptr, &image->bits_per_pixel, &image->line_length,&image->endian);
	return (image);
}

void	draw_square(t_data *data)
{
	int i = 0;
	int j = 0;

	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			t_image *image = create_image(data);
			my_mlx_pixel_put(image, 5, 5, 0x00FF0000);
			mlx_put_image_to_window(data->mlx, data->mlx_win, image->ptr, 0, 0);
			j++;
		}
		i++;
	}
}

void	run_game(t_data *data)
{
	//draw_square(data);
	//put_img(data, img, &data->mlx, &data->mlx_win);
	mlx_hook(data->mlx_win, 2, 0, get_events, data);
	// mlx_hook(data->mlx_win, 17, 0, exit_program, data);
	mlx_hook(data->mlx_win, 17, 1L << 0, exit_program, &data);
	mlx_loop(data->mlx);
}
