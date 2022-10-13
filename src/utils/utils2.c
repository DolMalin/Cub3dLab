/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:44:57 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/10/13 19:09:11 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_bool	is_near_charset(char **scene, size_t i, size_t j, char *charset)
{
	if (is_in_charset(scene[i + 1][j], charset)
		|| is_in_charset(scene[i - 1][j], charset)
			|| is_in_charset(scene[i][j + 1], charset)
				|| is_in_charset(scene[i][j - 1], charset))
		return (true);
	return (false);
}

t_bool	is_empty_line(char *line)
{
	int		i;

	i = 0;
	if (ft_strlen(line) == 1)
	{
		if (line[0] != '\n')
			return (false);
	}
	else
	{
		while (line[i])
		{
			if (!is_in_charset(line[i], " \0\n"))
				return (false);
			i++;
		}
	}
	return (true);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	printf("\e[2J");
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

t_bool	ft_strisdigit(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
