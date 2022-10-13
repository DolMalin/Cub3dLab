#include "../../includes/cub3d.h"

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
			if (!is_in_charset(map[i][j], "01NSEW "))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static	t_bool	check_map_closed(char **map)
{
	size_t	i;
	size_t	j;
	size_t	map_array_len;

	i = 0;
	map_array_len = array_len((void **)map);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (i == 0 || j == 0 || j == (ft_strlen(map[i]) - 1)
					|| i == map_array_len - 1)
					return (false);
				if (is_near_charset(map, i, j, " \0\n"))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

t_bool	check_map_len(char **scene)
{
	int		i;
	size_t	map_len;

	i = 0;
	map_len = 0;
	while (scene[i])
	{
		if (!is_config_line(scene[i]))
			map_len++;
		i++;
	}
	if (map_len < 3)
		return (false);
	return (true);
}

t_bool	check_map(char **scene)
{
	char	**map;

	map = get_map(scene);
	if (!check_map_len(scene))
	{
		free_array((void **)map);
		return (false);
	}
	if (!check_map_closed(map))
	{
		free_array((void **)map);
		return (false);
	}
	if (!check_valid_characters(map))
	{
		free_array((void **)map);
		return (false);
	}
	if (!check_player(map))
	{
		free_array((void **)map);
		return (false);
	}
	free_array((void **)map);
	return (true);
}
