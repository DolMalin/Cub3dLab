#include "../../includes/cub3d.h"

static t_bool	check_arguments(int ac, char **av)
{
	if (ac < 2)
	{
		printf("Please select a scene in arguments");
		return (0);
	}
	if (!ft_strnstr(av[1], ".cub", ft_strlen(av[1])))
	{
		printf("Not a .cub scene");
		return (0);
	}
	if (open(av[1], O_RDONLY) < 0)
	{
		printf("Can't access scene file");
		return (0);
	}
	return (1);
}

static t_bool	check_texture(char *texture_line, const char *texture_id)
{
	if (!texture_line)
	{
		printf("No texture found for %s walls\n", texture_id);
		return (false);
	}
	if (open(texture_line, O_RDONLY) < 0)
	{
		printf("Can't access the %s texture file\n", texture_id);
		return (false);
	}
	return (true);
}

static t_bool	check_textures(char **unparsed_scene)
{
	if (!check_texture(get_line_from_key(unparsed_scene, "NO"), "NO")) // verify if get_line_from_key gives path or line cf get path seems like it does
		return (false);
	if (!check_texture(get_line_from_key(unparsed_scene, "SO"), "SO"))
		return (false);
	if (!check_texture(get_line_from_key(unparsed_scene, "ES"), "ES"))
		return (false);
	if (!check_texture(get_line_from_key(unparsed_scene, "WE"), "WE"))
		return (false);
	return (true);
}

static t_bool	check_color(char **unparsed_scene)
{
	
}

static t_bool	check_colors(char **unparsed_scene)
{
	if (!check_color(get_line_from_key(unparsed_scene, "F")))
		return (false);
	if (!check_color(get_line_from_key(unparsed_scene, "C")))
		return (false);
	return (true);
}

t_bool	check_input(int ac, char **av)
{
	char	**unparsed_scene;

	unparsed_scene = parse_scene_file(av[1]);
	if (!check_arguments(ac, av))
		return (0);
	if (!check_textures(unparsed_scene))
		return (0);
	if (!check_colors(unparsed_scene(scene)))
	// check if duplicate texture : replace or return error
	return (1);
}