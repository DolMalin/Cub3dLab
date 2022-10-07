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
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'O'
					&& map[i][j] != 'E' && map[i][j] != 'W' && map[i][j] != ' ')
				return (false);
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
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
				start_pos++;
			j++;
		}
		i++;
	}
	if (start_pos != 1)
		return (false);
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
				if (is_near_void(map, i, j))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

t_bool	check_map(char **scene)
{
	char	**map;

	map = get_map(scene);
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
	free_array((void **)map);
	return (true);
}
