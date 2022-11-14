/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:46:38 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/14 14:43:02 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_bool	check_rgb_range(char *color)
{
	if (!(ft_atoi(color) >= 0 && (ft_atoi(color) <= 255)))
		return (false);
	return (true);
}

t_bool	check_color_code(char *color)
{
	char	*temp;

	temp = ft_strtrim(color, " ");
	if (!temp)
		error(MEMALLOC);
	if (ft_strlen(temp) > 3 || !ft_strisdigit(temp)
		|| !check_rgb_range(temp))
	{
		free(temp);
		return (false);
	}
	free(temp);
	return (true);
}

t_bool	check_color_codes(char *color)
{
	char	**split_color;
	int		i;

	split_color = ft_split(color, ',');
	if (!split_color)
		error(MEMALLOC);
	i = 0;
	while (split_color[i])
	{
		if (!check_color_code(split_color[i]))
		{
			free_array((void **)split_color);
			return (false);
		}
		i++;
	}
	if (i != 3)
	{
		free_array((void **)split_color);
		return (false);
	}
	free_array((void **)split_color);
	return (true);
}
