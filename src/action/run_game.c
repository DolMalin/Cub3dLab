#include "../../includes/cub3d.h"

char    get_player_token(t_data *data)
{
    size_t	i;
	size_t	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (is_in_charset(data->map[i][j], "NSEW"))
			{
                if (is_in_charset(data->map[i][j], "N"))
                    return ('N');
                else if (is_in_charset(data->map[i][j], "S"))
                    return ('S');
                else if (is_in_charset(data->map[i][j], "E"))
                    return ('E');
                return ('W');
			}
			j++;
		}
		i++;
	}
    return (0);
}

void	move_up(t_data **data)
{
	int		pos_x;
	int		pos_y;
	char	*player_pos;
	char	*dest_pos;

	pos_x = (*data)->x;
	pos_y = (*data)->y;
	player_pos = &(*data)->map[pos_y][pos_x];
	dest_pos = &(*data)->map[pos_y - 1][pos_x];
	if (*dest_pos == '1' || *dest_pos == ' ')
		return ;
    *dest_pos = get_player_token(*data);
    *player_pos = '0';
}

void	move_down(t_data **data)
{
	int		pos_x;
	int		pos_y;
	char	*player_pos;
	char	*dest_pos;

	pos_x = (*data)->x;
	pos_y = (*data)->y;
	player_pos = &(*data)->map[pos_y][pos_x];
	dest_pos = &(*data)->map[pos_y + 1][pos_x];
	if (*dest_pos == '1' || *dest_pos == ' ')
		return ;
    *dest_pos = get_player_token(*data);
    *player_pos = '0';
}

void	move_left(t_data **data)
{
	int		pos_x;
	int		pos_y;
	char	*player_pos;
	char	*dest_pos;

	pos_x = (*data)->x;
	pos_y = (*data)->y;
	player_pos = &(*data)->map[pos_y][pos_x];
	dest_pos = &(*data)->map[pos_y][pos_x - 1];
	if (*dest_pos == '1' || *dest_pos == ' ')
		return ;
    *dest_pos = get_player_token(*data);
    *player_pos = '0';
}

void	move_right(t_data **data)
{
	int		pos_x;
	int		pos_y;
	char	*player_pos;
	char	*dest_pos;

	pos_x = (*data)->x;
	pos_y = (*data)->y;
	player_pos = &(*data)->map[pos_y][pos_x];
	dest_pos = &(*data)->map[pos_y][pos_x + 1];
	if (*dest_pos == '1' || *dest_pos == ' ')
		return ;
    *dest_pos = get_player_token(*data);
    *player_pos = '0';
}

int	exec_action(int key, t_data *data)
{
    (void)data;
	update_user_pos(&data);
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
    {
        free_data(data);
        exit(EXIT_SUCCESS);
    }
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
	// put_img(data, img, &data->mlx, &data->mlx_win);
	mlx_hook(data->mlx_win, 2, 0, exec_action, data);
	// mlx_hook(data->mlx_win, 17, 0, exit_program, data);
	mlx_loop(data->mlx);
}
