#include "../../includes/cub3d.h"

t_bool	is_empty_space(char c)
{
	if (c == '\n' || c == ' ' || c == 0) // check if only cases of empty spaces in map - add '\t' ?
		return (true);
	return (false);
}

t_bool	is_near_void(char **unparsed_scene, size_t i, size_t j)
{
	if (is_empty_space(unparsed_scene[i + 1][j])
		|| is_empty_space(unparsed_scene[i - 1][j])
			|| is_empty_space(unparsed_scene[i][j + 1]) 
				|| is_empty_space(unparsed_scene[i][j - 1]))
		return (true);
	return (false);
}

t_bool	is_empty_line(char *line)
{
	int		i;

	i = 0;
	if (ft_strlen(line) == 1)
	{
		if (line[0] != '\n')
			return (false);
	}
	else
	{
		while (line[i])
		{
			if (!is_empty_space(line[i]))
				return (false);
			i++;
		}
	}
	return (true);
}

void print_map(char **map)
{
	int i;
	
	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

t_bool	ft_strisdigit(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}