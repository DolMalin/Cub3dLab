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
	if (ac < 0)
		return (false);
	if (!check_extension(av[1]))
		return (false);
	if (open(av[1], O_RDONLY) < 0)
	{
		//close fd
		return (false);
	}
	return (true);
}

t_bool	check_input(int ac, char **av)
{
	char	**scene;

	scene = parse_scene_file(av[1]);
	if (!check_arguments(ac, av))
		error(ARGS, (void **)scene);
	else if (!check_config_structure(scene))
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
