/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:46:45 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/10/18 13:02:38 by aandric          ###   ########lyon.fr   */
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
	{
		close(fd);
		return (false);
	}
	return (true);
}

t_bool	check_input(int ac, char **av)
{
	char	**scene;

	if (!check_arguments(ac, av))
	{
		printf("%s", ARGS);
		exit(EXIT_FAILURE);
		return(false);
	}
	scene = parse_scene_file(av[1]);
	if (!scene)
		exit(EXIT_FAILURE);
	if (!check_config_structure(scene))
		error(CONFIG_STRUCT, (void **)scene);
	else if (!check_colors(scene))
		error(RGB_CODES, (void **)scene);
	else if (!check_map(scene))
		error(MAP, (void **)scene);
	else if (!check_textures(scene))
		error(TEXTURES, (void **)scene);
	free_array((void **)scene);
	return (true);
}
