/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:40:25 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/10 17:09:35 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_up(t_data **data)
{
	float	next_x;
	float	next_y;
	int		next_x_i;
	int		next_y_i;

	next_x = (*data)->player->x + (*data)->player->ray_coef_x * STEP_COEF;
	next_y = (*data)->player->y - (*data)->player->ray_coef_y * STEP_COEF;
	next_x_i = (*data)->player->x + (*data)->player->ray_coef_x
		* (STEP_COEF + HIT_BOX);
	next_y_i = (*data)->player->y - (*data)->player->ray_coef_y
		* (STEP_COEF + HIT_BOX);
	if ((*data)->map[next_y_i][next_x_i] == '1')
		return ;
	(*data)->player->x = next_x;
	(*data)->player->y = next_y;
}

void	move_down(t_data **data)
{
	float	next_x;
	float	next_y;
	int		next_x_i;
	int		next_y_i;

	next_x = (*data)->player->x - (*data)->player->ray_coef_x * STEP_COEF;
	next_y = (*data)->player->y + (*data)->player->ray_coef_y * STEP_COEF;
	next_x_i = (*data)->player->x - (*data)->player->ray_coef_x
		* (STEP_COEF + HIT_BOX);
	next_y_i = (*data)->player->y + (*data)->player->ray_coef_y
		* (STEP_COEF + HIT_BOX);
	if ((*data)->map[next_y_i][next_x_i] == '1')
		return ;
	(*data)->player->x = next_x;
	(*data)->player->y = next_y;
}

void	move_left(t_data **data)
{
	float	next_x;
	float	next_y;
	int		next_x_i;
	int		next_y_i;

	next_x = (*data)->player->x - (*data)->player->ray_coef_y * STEP_COEF;
	next_y = (*data)->player->y - (*data)->player->ray_coef_x * STEP_COEF;
	next_x_i = (*data)->player->x - (*data)->player->ray_coef_x
		* (STEP_COEF + HIT_BOX);
	next_y_i = (*data)->player->y - (*data)->player->ray_coef_y
		* (STEP_COEF + HIT_BOX);
	if ((*data)->map[next_y_i][next_x_i] == '1')
		return ;
	(*data)->player->x = next_x;
	(*data)->player->y = next_y;
}

void	move_right(t_data **data)
{
	float	next_x;
	float	next_y;
	int		next_x_i;
	int		next_y_i;

	next_x = (*data)->player->x + (*data)->player->ray_coef_y * STEP_COEF;
	next_y = (*data)->player->y + (*data)->player->ray_coef_x * STEP_COEF;
	next_x_i = (*data)->player->x + (*data)->player->ray_coef_x
		* (STEP_COEF + HIT_BOX);
	next_y_i = (*data)->player->y + (*data)->player->ray_coef_y
		* (STEP_COEF + HIT_BOX);
	if ((*data)->map[next_y_i][next_x_i] == '1')
		return ;
	(*data)->player->x = next_x;
	(*data)->player->y = next_y;
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
