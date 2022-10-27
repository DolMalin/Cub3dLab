/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:46:45 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/10/27 15:31:13 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_bool	check_extension(const char *file_path)
{
	size_t	i;

	i = ft_strlen(file_path) - 1;
	while (i && file_path[i] != '.')
		i--;
	if (ft_strncmp(&file_path[i], ".cub", 5) != 0)
		return (false);
	return (true);
}

static t_bool	check_arguments(int ac, char **av)
{
	int		fd;

	if (ac < 2)
		return (false);
	if (!check_extension(av[1]))
		return (false);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}

t_bool	check_input(int ac, char **av)
{
	char	**scene;

	scene = parse_scene_file(av[1]);
	if (!scene)
		error(MEMALLOC);
	if (!check_arguments(ac, av))
		error(ARGS);
	else if (!check_config_structure(scene))
		error(CONFIG_STRUCT);
	else if (!check_colors(scene))
		error(RGB_CODES);
	else if (!check_map(scene))
		error(MAP);
	else if (!check_textures(scene))
		error(TEXTURES);
	free_array((void **)scene);
	return (true);
}
