/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:14:00 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/10/13 16:19:50 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

size_t	filled_lines_len(char **parsed_scene)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (parsed_scene[i])
	{
		if (!is_empty_line(parsed_scene[i]))
			len++;
		i++;
	}
	return (len);
}

char	**remove_empty_lines(char **parsed_scene)
{
	size_t	i;
	size_t	j;
	char	**output;

	i = 0;
	j = 0;
	output = malloc(sizeof(char *) * (filled_lines_len(parsed_scene) + 1));
	if (!output)
		return (NULL);
	while (parsed_scene[i])
	{
		if (!is_empty_line(parsed_scene[i]))
		{
			output[j] = ft_strdup(parsed_scene[i]);
			j++;
		}
		i++;
	}
	output[j] = 0;
	free_array((void **)parsed_scene);
	return (output);
}

char	**parse_scene_file(char *scene_file)
{
	char	**parsed_scene;
	int		i;
	int		fd;

	i = 0;
	fd = open(scene_file, O_RDONLY);
	parsed_scene = malloc(sizeof(char *) * (lines_count(scene_file) + 1));
	if (!parsed_scene)
		return (NULL);
	parsed_scene[i] = get_next_line(fd);
	while (parsed_scene[i])
	{
		i++;
		parsed_scene[i] = get_next_line(fd);
	}
	parsed_scene[i] = NULL;
	parsed_scene = remove_empty_lines(parsed_scene);
	parsed_scene = trim_config_line(parsed_scene);
	if (!parsed_scene)
		return (NULL);
	return (parsed_scene);
}
