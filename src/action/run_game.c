#include "../../includes/cub3d.h"



int	exec_action(int key, t_data *data)
{
    (void)data;
	// update_user_pos(&data);
	if (key == KB_W)
		printf("UP\n");
	else if (key == KB_A)
		printf("LEFT\n");
	else if (key == KB_D)
		printf("LEFT\n");
	else if (key == KB_S)
		printf("DOWN\n");
	// else if (key == KEY_ESC)
	// 	exit_program(data);
	return (0);
}

void	run_game(t_data *data)
{
	// put_img(data, img, &data->mlx, &data->mlx_win);
	mlx_hook(data->mlx_win, 2, 0, exec_action, data);
	// mlx_hook(data->mlx_win, 17, 0, exit_program, data);
	mlx_loop(data->mlx);
}
