/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_features_from_scene.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:25:27 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/03 13:29:35 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*get_line_from_key(char **parsed_scene, char *key)
{
	int		i;
	char	*buff;

	i = 0;
	while (parsed_scene[i])
	{
		if (ft_strncmp(parsed_scene[i], key, ft_strlen(key)) == 0)
		{
			if (parsed_scene[i][0] == 'C' || parsed_scene[i][0] == 'F')
			{
				if (ft_strlen(&parsed_scene[i][1]) == 0)
					return (NULL);
				buff = ft_strdup(&parsed_scene[i][1]);
				if (!buff)
					error(MEMALLOC);
				return (buff);
			}
			if (ft_strlen(&parsed_scene[i][2]) == 0)
				return (NULL);
			buff = ft_strdup(&parsed_scene[i][2]);
			if (!buff)
				error(MEMALLOC);
			return (buff);
		}
		i++;
	}
	return (NULL);
}

unsigned char	*get_color(char *line)
{
	unsigned char	*color;
	char			**splited_line;

	splited_line = ft_split(line, ',');
	if (!splited_line)
		error(MEMALLOC);
	color = malloc(sizeof(unsigned char) * 3);
	if (!color)
		error(MEMALLOC);
	color[R] = (unsigned char)ft_atoi(splited_line[0]);
	color[G] = (unsigned char)ft_atoi(splited_line[1]);
	color[B] = (unsigned char)ft_atoi(splited_line[2]);
	free_array((void **)splited_line);
	free(line);
	return (color);
}

unsigned char	**get_colors(char **parsed_scene)
{
	unsigned char	**colors;

	colors = malloc(sizeof(char *) * 3);
	if (!colors)
		error(MEMALLOC);
	colors[FLOOR] = get_color(get_line_from_key(parsed_scene, "F"));
	colors[CEIL] = get_color(get_line_from_key(parsed_scene, "C"));
	return (colors);
}

char	**get_textures_paths(char **parsed_scene)
{
	char	**textures_paths;

	textures_paths = malloc(sizeof(char *) * 4);
	if (!textures_paths)
		return (NULL);
	textures_paths[NO] = get_line_from_key(parsed_scene, "NO");
	textures_paths[SO] = get_line_from_key(parsed_scene, "SO");
	textures_paths[EA] = get_line_from_key(parsed_scene, "EA");
	textures_paths[WE] = get_line_from_key(parsed_scene, "WE");
	return (textures_paths);
}
