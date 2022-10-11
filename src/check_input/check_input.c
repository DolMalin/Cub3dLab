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
	if (ac < 2)
	{
		printf("Error: no scene in arguments\n");
		return (false);
	}
	if (!check_extension(av[1]))
	{
		printf("Error: not a .cub scene file\n");
		return (false);
	}
	if (open(av[1], O_RDONLY) < 0)
	{
		printf("Error: can't access scene file\n");
		return (false);
	}
	return (true);
}

t_bool	check_input(int ac, char **av)
{
	char	**scene;

	scene = parse_scene_file(av[1]);
	if (!check_arguments(ac, av))
		return (error(OTHER_ERRORS, scene));
	if (!check_config_structure(scene))
		return (error(OTHER_ERRORS, scene));
	if (!check_map(scene))
		return (error(OTHER_ERRORS, scene));
	if (!check_textures(scene))
		return (error(OTHER_ERRORS, scene));
	if (!check_colors(scene))
		return (error(OTHER_ERRORS, scene));
	free_array((void **)scene);
	return (true);
}
