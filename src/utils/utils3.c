/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:46:04 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/14 15:01:35 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_bool	is_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (true);
		i++;
	}
	return (false);
}

int	get_max_x(char	**parsed_scene)
{
	int		i;
	int		j;
	int		buff_len;
	int		max_len;

	i = 0;
	j = 0;
	buff_len = 0;
	max_len = 0;
	while (parsed_scene[i])
	{
		if (!is_config_line(parsed_scene[i]))
		{
			buff_len = ft_strlen(parsed_scene[i]);
			if (buff_len > max_len)
				max_len = buff_len;
			j++;
		}
		i++;
	}
	return (max_len);
}

int	get_start_map(char **parsed_scene)
{
	int	i;

	i = 0;
	while (parsed_scene[i])
	{
		if (is_config_line(parsed_scene[i]) || parsed_scene[i][0] == '\n')
			i++;
		else
			break ;
	}
	return (i);
}
