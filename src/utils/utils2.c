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
	int	i;

	i = 0;

	while (line[i])
	{
		if (line[i] == '\n')
			return (true);
		i++;
	}
	return (false);
}
