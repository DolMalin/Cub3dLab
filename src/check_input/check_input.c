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

// static t_bool   check_color(char *color_line, const char *color_id)
// {
//     unsigned char   *color;
//     char            **splited_line;

//     splited_line = ft_split(color_line, ',');
//     if (!splited_line)
//         return (false);
//     color = malloc(sizeof(unsigned char) * 3);
//     if (!color)
//         return (false);
//     color[R] = (unsigned char)ft_atoi(&splited_line[0][2]);
//     color[G] = (unsigned char)ft_atoi(splited_line[1]);
//     color[B] = (unsigned char)ft_atoi(splited_line[2]); // make a function to get the color and seperate from check_color
//     // the condition below condition condition simplified
//     if (!((color[R] >= 0 && color[R] <= 255) 
//         && (color[G] >= 0 && color[R] <= 255) 
//             && (color[B] >= 0 && color[R] <= 255)))
//     {
//             free(color);
//             free(splited_line);
//             printf("Wrong RGB color code for %s definition\n", color_id);
//             return (false);
//     }
//     free(color);
//     free(splited_line);
//     return (true); // think about the case when there is nothing between 2 "," example : "200,,300"
// }

// static t_bool   check_colors(char **unparsed_scene)
// {
//     if (!check_color(get_line_from_key(unparsed_scene, "F"), "Floor")) // find a way to verify if the line is missing to have an error message "no floor color code indicated"
//         return (false);
//     if (!check_color(get_line_from_key(unparsed_scene, "C"), "Ceiling"))
//         return (false);
//     return (true);
// }

static	t_bool	check_map_closed(char **map)
{
	size_t	i;
	size_t	j;
	size_t	map_array_len;

	i = 0;
	map_array_len = array_len((void**)map);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (i == 0 || j == 0 || j == (ft_strlen(map[i]) - 1) || i == map_array_len - 1)
					return (false);
				if (is_near_void(map, i, j))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

static t_bool	check_one_start_pos(char **map)
{
	int	i;
	int	j;
	int	start_pos;

	i = 0;
	start_pos = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] ==  'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
				start_pos++;
			j++;
		}
		i++;
	}
	if (start_pos != 1)
		return (false);
	return (true);
}

static t_bool	check_valid_characters(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N' 
				&& map[i][j] != 'S' && map[i][j] != 'O' 
					&& map[i][j] != 'E' && map[i][j] != 'W')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static t_bool	check_map(char **unparsed_scene)
{
	char	**map;

	map = get_map(unparsed_scene);
	// print_map(map);
	if (!check_map_closed(map))
	{
		printf("The map is not closed\n");
		free_array((void **)map);
		return (false);
	}
	if (!check_valid_characters(map))
	{
		printf("Invalid characters in the map\n");
		free_array((void **)map);
		return (false);
	}
	if (!check_one_start_pos(map))
	{
		printf("There is more than one or no starting position for player\n");
		free_array((void **)map);
		return (false);
	}
	// printf("map is ok\n");
	free_array((void **)map);
	return (true);
}

t_bool  check_input(int ac, char **av)
{
    char    **unparsed_scene;
    (void)ac;
    unparsed_scene = parse_scene_file(av[1]);
    if (!check_arguments(ac, av))
    {
        free_array((void**)unparsed_scene);
        return (false);
    }/*
    if (!check_textures(unparsed_scene))
    {
        free(unparsed_scene);
        return (false);
    }
    if (!check_colors(unparsed_scene))
    {
        free(unparsed_scene);
        return (false);
    }*/
	if (!check_map(unparsed_scene))
	{
		printf("Map is incorrect \n");
		free_array((void **)unparsed_scene);
        return (false);
	}
    // check if duplicate texture : replace or return error
    free_array((void **)unparsed_scene);
    return (true);
}