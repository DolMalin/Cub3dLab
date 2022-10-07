#include "../../includes/cub3d.h"

static t_bool	check_arguments(int ac, char **av)
{
	if (ac < 2)
	{
		printf("No scene in arguments\n");
		return (0);
	}
	// This condition check if the .cub is only at the end on the file and has nothing after ? i.e michel.cubmichel
	if (!ft_strnstr(av[1], ".cub", ft_strlen(av[1])))
	{
		printf("Not a .cub scene file\n");
		return (0);
	}
	if (open(av[1], O_RDONLY) < 0)
	{
		printf("Can't access scene file\n");
		return (0);
	}
	return (1);
}

static t_bool	check_config_line_missing(char **scene)
{
	if (!get_line_from_key(scene, "NO")
		||!get_line_from_key(scene, "SO")
		|| !get_line_from_key(scene, "EA")
		|| !get_line_from_key(scene, "WE"))
	{
		printf("Error: texture missing for NO, SO, EA or WE.\n");
		return (false);
	}
	if (!get_line_from_key(scene, "C")
		|| !get_line_from_key(scene, "F"))
	{
		printf("Error: color missing for floor or cieling.\n");
		return (false);
	}
	return (true);
}

static t_bool	check_structure(char **scene)
{
	int	i;

	i = 0;
	while (is_config_line(scene[i]))
		i++;
	while (scene[i])
	{
		if (is_config_line(scene[i]))
		{
			printf("Error: incorrect structure of scene.\n");
			return (false);
		}
		i++;
	}
	return (true);
}

static t_bool	check_config_structure(char **scene)
{
	if (!check_config_line_missing(scene))
		return (false);
	if (!check_structure(scene))
		return (false);
	return (true);
}

t_bool	check_input(int ac, char **av)
{
	char	**scene;

	scene = parse_scene_file(av[1]);
	if (!check_arguments(ac, av))
	{
		free_array((void **)scene);
		return (false);
	}
	if (!check_config_structure(scene))
	{
		free_array((void **)scene);
		return (false);
	}
	// if (!check_textures(scene))
	// {
	//     free_array((void **)scene);
	//     return (false);
	// }
	if (!check_colors(scene))
	{
		free_array((void **)scene);
		return (false);
	}
	if (!check_map(scene))
	{
		printf("Map is incorrect \n");
		free_array((void **)scene);
		return (false);
	}
	printf("Everything ok\n");
	free_array((void **)scene);
	return (true);
}
