/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:26:05 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/11 16:29:49 by pdal-mol         ###   ########.fr       */
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

static char	*complete_line_with_space(char *line, int len)
{
	char	*output;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(line);
	if (i == len)
		return (line);
	output = malloc(sizeof(char) * (len + 1));
	if (!output)
		error(MEMALLOC);
	while (j < i)
	{
		output[j] = line[j];
		j++;
	}
	while (i < len)
	{
		output[i] = ' ';
		i++;
	}
	output[i] = 0;
	free(line);
	return (output);
}

int	get_max_x(char	**parsed_scene)
{
	int		i;
	int		j;
	int		buff_len;
	int		max_len;

	i = 0;
	j = 0;
	buff_len = 0;
	max_len = 0;
	while (parsed_scene[i])
	{
		if (!is_config_line(parsed_scene[i]))
		{
			buff_len = ft_strlen(parsed_scene[i]);
			if (buff_len > max_len)
				max_len = buff_len;
			j++;
		}
		i++;
	}
	return (max_len);
}

char	**get_map(char	**parsed_scene)
{
	char	**map;
	int		i;
	int		j;
	int		max_x;

	i = 0;
	j = 0;
	if (map_len(parsed_scene) == 0)
		return (NULL);
	map = malloc(sizeof(char *) * (map_len(parsed_scene) + 1));
	if (!map)
		error(MEMALLOC);
	max_x = get_max_x(parsed_scene);
	while (parsed_scene[i])
	{
		if (!is_config_line(parsed_scene[i]))
		{
			map[j] = ft_strtrim(parsed_scene[i], "\n");
			if (!map[j])
				return (NULL);
			map[j] = complete_line_with_space(map[j], max_x);
			j++;
		}
		i++;
	}
	map[j] = 0;
	return (map);
}
