/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:40:15 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/10/17 11:52:31 by aandric          ###   ########lyon.fr   */
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
	//print_map(data->map);
	run_game(data);
	free_data(data);
	return (0);
}
