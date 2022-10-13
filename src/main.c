/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:40:15 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/10/13 18:06:45 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int	main(int ac, char **av)
{
	t_data	*data;

	if (!check_input(ac, av))
		return (1);
	data = init_data(av[1]);
	if (!data)
		exit(EXIT_FAILURE);
	print_map(data->map);
	run_game(data);
	free_data(data);
	return (0);
}
