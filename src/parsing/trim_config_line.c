/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_config_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:19:54 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/03 13:24:28 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static size_t	get_trim_len(char *line, char *charset)
{
	size_t	i;
	size_t	s_count;

	i = 0;
	s_count = 0;
	if (ft_strlen(line) <= 0)
		return (s_count);
	while (line[i])
	{
		if (!is_in_charset(line[i], charset))
			s_count++;
		i++;
	}
	return (s_count);
}

char	*trim(char *line, char *charset)
{
	char	*trimed_line;
	int		i;
	int		k;

	i = 0;
	if (get_trim_len(line, charset) == 0)
		return (NULL);
	trimed_line = malloc(sizeof(char) * (get_trim_len(line, charset) + 1));
	if (!trimed_line)
		error(MEMALLOC);
	k = 0;
	while (line[i])
	{
		if (!is_in_charset(line[i], charset))
		{
			trimed_line[k] = line[i];
			k++;
		}
		i++;
	}
	trimed_line[k] = '\0';
	return (trimed_line);
}

char	**trim_config_line(char **parsed_scene)
{
	char	**trimed_scene;
	int		i;

	i = 0;
	trimed_scene = malloc(sizeof(char *)
			* (array_len((void **)parsed_scene) + 1));
	if (!trimed_scene)
		error(MEMALLOC);
	while (parsed_scene[i])
	{
		if (is_config_line(parsed_scene[i]))
			trimed_scene[i] = trim(parsed_scene[i], " \n\t");
		else
			trimed_scene[i] = ft_strdup(parsed_scene[i]);
		free(parsed_scene[i]);
		i++;
	}
	trimed_scene[i] = 0;
	free(parsed_scene);
	return (trimed_scene);
}
