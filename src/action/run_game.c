/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:40:40 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/03 13:19:36 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	exit_program(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}

int	get_events(int key, t_data *data)
{
	if (key == ESCAPE_KC)
		exit_program(data);
	move_player(data, key);
	print_config(data);
	create_image(data);
	return (0);
}

void	run_game(t_data *data)
{
	create_image(data);
	mlx_hook(data->mlx_win, 2, 0, get_events, data);
	mlx_hook(data->mlx_win, 17, 0, exit_program, data);
	mlx_loop(data->mlx);
}
