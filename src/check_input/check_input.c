#include "../../includes/cub3d.h"

static t_bool   check_arguments(int ac, char **av)
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

// static t_bool   check_texture(char *texture_line, const char *texture_id)
// {
//     if (!texture_line)
//     {
//         printf("No texture found for %s walls\n", texture_id);
//         return (false);
//     }
//     if (open(texture_line, O_RDONLY) < 0)
//     {
//         printf("Can't access the %s texture file\n", texture_id);
//         return (false);
//     }
//     return (true);
// }

// static t_bool   check_textures(char **unparsed_scene)
// {
//     if (!check_texture(get_line_from_key(unparsed_scene, "NO"), "NO")) // verify if get_line_from_key gives path or line cf get path seems like it does
//         return (false);
//     if (!check_texture(get_line_from_key(unparsed_scene, "SO"), "SO")) // verify how to free linke from key
//         return (false);
//     if (!check_texture(get_line_from_key(unparsed_scene, "ES"), "ES"))
//         return (false);
//     if (!check_texture(get_line_from_key(unparsed_scene, "WE"), "WE"))
//         return (false);
//     return (true);
// }

static t_bool	check_config_line_missing(char **unparsed_scene)
{
	if (!get_line_from_key(unparsed_scene, "NO") || !get_line_from_key(unparsed_scene, "SO")
		|| !get_line_from_key(unparsed_scene, "EA") || !get_line_from_key(unparsed_scene, "WE"))
	{
		printf("Missing configuration line about walls texture : NO, SO, EA or WE.\n");
		return (false);
	}
	if (!get_line_from_key(unparsed_scene, "C") || !get_line_from_key(unparsed_scene, "F"))
	{
		printf("Missing configuration line about colors: floor or ceiling.\n");
		return (false);
	}
	return (true);
}

static t_bool check_structure(char **unparsed_scene)
{
	int	i;

	i = 0;
	while (is_config_line(unparsed_scene[i]))
		i++;
	while (unparsed_scene[i])
	{
		if (is_config_line(unparsed_scene[i]))
		{
			printf("Configuration lines must be at the begining of the file followed by the map.\n");
			return (false);
		}
		i++;
	}
	return (true);
}

t_bool  check_input(int ac, char **av)
{
    char    **unparsed_scene;
    (void)ac;
    unparsed_scene = parse_scene_file(av[1]);
	//print_map(unparsed_scene);
    if (!check_arguments(ac, av))
    {
        free_array((void**)unparsed_scene);
        return (false);
    }
	if (!check_config_line_missing(unparsed_scene))
	{
		free_array((void **)unparsed_scene);
		return (false);
	}
	if (!check_structure(unparsed_scene))
	{
		free_array((void **)unparsed_scene);
		return (false);
	}
    // if (!check_textures(unparsed_scene))
    // {
    //     free_array((void **)unparsed_scene);
    //     return (false);
    // }
    if (!check_colors(unparsed_scene))
    {
        free_array((void **)unparsed_scene);
        return (false);
    }
	if (!check_map(unparsed_scene))
	{
		printf("Map is incorrect \n");
		free_array((void **)unparsed_scene);
        return (false);
	}
	printf("Everything ok\n");
    free_array((void **)unparsed_scene);
    return (true);
}
