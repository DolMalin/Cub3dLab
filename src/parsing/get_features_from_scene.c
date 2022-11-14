/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_features_from_scene.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:25:27 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/14 14:46:07 by pdal-mol         ###   ########.fr       */
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
