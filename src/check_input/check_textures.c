/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:46:51 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/11 15:24:40 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_bool	check_texture(char *texture_path)
{
	size_t	i;
	int		fd;

	if (!texture_path)
		return (false);
	i = ft_strlen(texture_path) - 1;
	while (i && texture_path[i] != '.')
		i--;
	if (ft_strncmp(&texture_path[i], ".xpm", 5) != 0)
		return (false);
	fd = open(texture_path, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (false);
	}
	return (true);
}

t_bool	check_textures(char **scene)
{
	char	*buffer;
	int		i;

	i = 0;
	while (i < 4)
	{
		if (i == NO)
			buffer = get_line_from_key(scene, "NO");
		else if (i == SO)
			buffer = get_line_from_key(scene, "SO");
		else if (i == EA)
			buffer = get_line_from_key(scene, "EA");
		else if (i == WE)
			buffer = get_line_from_key(scene, "WE");
		if (!buffer)
			return (false);
		
		if (!check_texture(buffer))
		{
			free(buffer);
			return (false);
		}
		free(buffer);
		i++;
	}
	return (true);
}
