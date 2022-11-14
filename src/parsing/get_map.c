/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:26:05 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/14 15:32:25 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	map_len(char **parsed_scene)
{
	int	map_len;
	int	i;

	map_len = 0;
	i = get_start_map(parsed_scene);
	if (i == (int)array_len((void **)parsed_scene))
		return (0);
	while (parsed_scene[i])
	{
		i++;
		map_len++;
	}
	i--;
	while (i >= 0 && parsed_scene[i][0] == '\n')
	{
		i--;
		map_len--;
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

char	*filter_map_line(char *line, int max_x)
{
	char	*output;

	output = line;
	if (ft_strlen(line) > 1)
	{
		output = ft_strtrim(line, "\n");
		if (!output)
			return (MEMALLOC);
	}
	output = complete_line_with_space(output, max_x);
	return (output);
}

char	**get_map(char **parsed_scene)
{
	char	**map;
	int		i;
	int		j;
	int		max_x;

	j = 0;
	if (map_len(parsed_scene) == 0)
		return (NULL);
	map = malloc(sizeof(char *) * (map_len(parsed_scene) + 1));
	if (!map)
		error(MEMALLOC);
	max_x = get_max_x(parsed_scene);
	i = get_start_map(parsed_scene);
	while (j < map_len(parsed_scene))
	{
		map[j] = filter_map_line(parsed_scene[i], max_x);
		j++;
		i++;
	}
	map[j] = 0;
	return (map);
}
