/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:26:05 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/11 14:59:09 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

size_t	map_len(char	**parsed_scene)
{
	size_t	map_len;
	size_t	i;

	map_len = 0;
	i = 0;
	while (parsed_scene[i])
	{
		if (!is_config_line(parsed_scene[i]))
			map_len++;
		i++;
	}
	return (map_len);
}

char	**get_map(char	**parsed_scene)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (map_len(parsed_scene) == 0)
		return (NULL);
	map = malloc(sizeof(char *) * (map_len(parsed_scene) + 1));
	if (!map)
		error(MEMALLOC);
	while (parsed_scene[i])
	{
		if (!is_config_line(parsed_scene[i]))
		{
			map[j] = ft_strtrim(parsed_scene[i], "\n");
			if (!map[j])
				return (NULL);
			j++;
		}
		i++;
	}
	map[j] = 0;
	return (map);
}
