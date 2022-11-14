/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_config_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:19:54 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/14 14:06:06 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
			trimed_scene[i] = ft_strtrim(parsed_scene[i], " \n\t");
		else
			trimed_scene[i] = ft_strdup(parsed_scene[i]);
		free(parsed_scene[i]);
		i++;
	}
	trimed_scene[i] = 0;
	free(parsed_scene);
	return (trimed_scene);
}
