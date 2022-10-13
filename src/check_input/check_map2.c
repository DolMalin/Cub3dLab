/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:46:49 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/10/13 16:46:50 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_bool	check_player_is_in_map(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_in_charset(map[i][j], "NSEW"))
			{
				if (i == 0 || j == 0 || i == array_len((void **)map)
					|| j == ft_strlen(map[i]) - 1)
					return (false);
				else if (ft_strlen(map[i - 1]) < j || ft_strlen(map[i + 1]) < j)
					return (false);
				else if (is_near_charset(map, i, j, " "))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

static t_bool	check_one_player(char **map)
{
	size_t	i;
	size_t	j;
	size_t	player_nb;

	i = 0;
	player_nb = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_in_charset(map[i][j], "NSEW"))
				player_nb ++;
			j++;
		}
		i++;
	}
	if (player_nb != 1)
		return (false);
	return (true);
}

t_bool	check_player(char **map)
{
	if (!check_one_player(map))
		return (false);
	if (!check_player_is_in_map(map))
		return (false);
	return (true);
}
