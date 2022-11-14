/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:46:47 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/14 15:32:55 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	t_bool	check_map_closed(char **map)
{
	size_t	i;
	size_t	j;
	size_t	map_array_len;

	i = 0;
	map_array_len = array_len((void **)map);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (i == 0 || j == 0 || j == (ft_strlen(map[i]) - 1)
					|| i == map_array_len - 1)
					return (false);
				if (is_near_charset(map, i, j, " \0\n"))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

t_bool	check_map_len(char **map)
{
	size_t	map_len;

	map_len = array_len((void **)map);
	if (map_len < 2)
		return (false);
	return (true);
}

t_bool	check_map(char **scene)
{
	char	**map;

	map = get_map(scene);
	if (!map)
		return (false);
	if (!check_map_len(map))
	{
		free_array((void **)map);
		return (false);
	}
	if (!check_map_closed(map))
	{
		free_array((void **)map);
		return (false);
	}
	if (!check_player(map))
	{
		free_array((void **)map);
		return (false);
	}
	free_array((void **)map);
	return (true);
}
