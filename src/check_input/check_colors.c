/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:46:35 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/14 13:52:24 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	**get_colors_to_check(char **scene)
{
	char	**colors;

	colors = malloc(sizeof(char *) * 2);
	if (!colors)
		error(MEMALLOC);
	colors[FLOOR] = get_line_from_key(scene, "F");
	colors[CEIL] = get_line_from_key(scene, "C");
	return (colors);
}

static int	coma_count(char *color)
{
	int	i;
	int	coma_count;

	i = 0;
	coma_count = 0;
	while (color[i])
	{
		if (color[i] == ',')
			coma_count++;
		i++;
	}
	return (coma_count);
}

static t_bool	check_comas(char **colors)
{
	if (coma_count(colors[CEIL]) != 2)
		return (false);
	if (coma_count(colors[FLOOR]) != 2)
		return (false);
	return (true);
}

static t_bool	check_line_color(char **scene)
{
	char	*buffer;
	int		i;

	i = 0;
	while (i < 2)
	{
		if (i == FLOOR)
			buffer = get_line_from_key(scene, "F");
		else if (i == CEIL)
			buffer = get_line_from_key(scene, "C");
		if (!buffer)
			return (false);
		free(buffer);
		i++;
	}
	return (true);
}

t_bool	check_colors(char **scene)
{
	char	**colors;

	colors = get_colors_to_check(scene);
	if (!check_line_color(scene))
		return (false);
	if (!check_comas(colors))
	{
		free_unterminated_array((void **)colors, 2);
		return (false);
	}
	if (!check_color_code(colors[FLOOR]))
	{
		free_unterminated_array((void **)colors, 2);
		return (false);
	}
	if (!check_color_code(colors[CEIL]))
	{
		free_unterminated_array((void **)colors, 2);
		return (false);
	}
	free_unterminated_array((void **)colors, 2);
	return (true);
}
