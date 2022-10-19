#include "../../includes/cub3d.h"

// void	get_player_pos(t_data **data)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	while ((*data)->map[i])
// 	{
// 		j = 0;
// 		while ((*data)->map[i][j])
// 		{
// 			if (is_in_charset((*data)->map[i][j], "NSEW"))
// 			{
// 				(*data)->y = i;
// 				(*data)->x = j;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	move_up(t_data **data)
{
	float next_x;
	float next_y;
	int	next_x_i;
	int	next_y_i;

	next_x = (*data)->player->x;
	next_y = (*data)->player->y - STEP_COEF;
	next_x_i = (int)floor(next_x);
	next_y_i = (int)floor(next_y);
	if ((*data)->map[next_y_i][next_x_i] == '1')
		return ;
	(*data)->player->y = next_y;
}

void	move_down(t_data **data)
{
	float next_x;
	float next_y;
	int	next_x_i;
	int	next_y_i;

	next_x = (*data)->player->x;
	next_y = (*data)->player->y + STEP_COEF;
	next_x_i = (int)floor(next_x);
	next_y_i = (int)floor(next_y);
	if ((*data)->map[next_y_i][next_x_i] == '1')
		return ;
	(*data)->player->y = next_y;
}

void	move_left(t_data **data)
{
	float next_x;
	float next_y;
	int	next_x_i;
	int	next_y_i;

	next_x = (*data)->player->x - STEP_COEF;
	next_y = (*data)->player->y;
	next_x_i = (int)floor(next_x);
	next_y_i = (int)floor(next_y);
	if ((*data)->map[next_y_i][next_x_i] == '1')
		return ;
	(*data)->player->x = next_x;
}

void	move_right(t_data **data)
{
	float next_x;
	float next_y;
	int	next_x_i;
	int	next_y_i;

	next_x = (*data)->player->x + STEP_COEF;
	next_y = (*data)->player->y;
	next_x_i = (int)floor(next_x);
	next_y_i = (int)floor(next_y);
	if ((*data)->map[next_y_i][next_x_i] == '1')
		return ;
	(*data)->player->x = next_x;
}

int	move_player(t_data *data, int key)
{
	if (key == KB_W)
		move_up(&data);
	else if (key == KB_A)
		move_left(&data);
	else if (key == KB_D)
		move_right(&data);
	else if (key == KB_S)
		move_down(&data);
	else if (key == KB_LEFT)
		rotate_left(&data);
	else if (key == KB_RIGHT)
		rotate_right(&data);
	return (0);
}
