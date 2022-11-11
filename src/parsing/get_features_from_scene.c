/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_features_from_scene.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:25:27 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/11 17:33:24 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*remove_key(char *line, char *key)
{
	char	*buff;
	int		i;
	int		key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (ft_strncmp(line, key, key_len) != 0)
		i++;
	i += key_len;
	while (is_in_charset(line[i], " \t\r"))
		i++;
	buff = ft_strdup(&line[i]);
	if (!buff)
		error(MEMALLOC);
	return (buff);
}

char	*get_line_from_key(char **parsed_scene, char *key)
{
	int		i;

	i = 0;
	while (parsed_scene[i])
	{
		if (ft_strncmp(parsed_scene[i], key, ft_strlen(key)) == 0)
			return (remove_key(parsed_scene[i], key));
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
		return (NULL);
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
