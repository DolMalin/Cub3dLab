/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:45:31 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/14 14:57:10 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**trim_array(char **splited_line, char *charset)
{
	char	*temp;
	int		i;

	i = 0;
	while (splited_line[i])
	{
		temp = splited_line[i];
		splited_line[i] = ft_strtrim(splited_line[i], charset);
		if (!splited_line[i])
			error(MEMALLOC);
		free(temp);
		i++;
	}
	return (splited_line);
}

unsigned char	*get_color(char *line)
{
	unsigned char	*color;
	char			**splited_line;
	int				i;

	splited_line = ft_split(line, ',');
	if (!splited_line)
		error(MEMALLOC);
	i = 0;
	splited_line = trim_array(splited_line, " ");
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
