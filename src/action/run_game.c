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
	if (key == ESCAPE_KC)
		exit_program(data);
	move_player(data, key);
	return (0);
}

void	run_game(t_data *data)
{
	mlx_hook(data->mlx_win, 2, 0, get_events, data);
	mlx_loop_hook(data->mlx, create_image, data);
	mlx_hook(data->mlx_win, 17, 1L << 0, exit_program, &data);
	mlx_loop(data->mlx);
}
