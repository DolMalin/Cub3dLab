#include "../../includes/cub3d.h"

t_bool is_in_charset(char c, char *charset)
{
	int	i;

	i = 0;

	while (charset[i])
	{
		if (charset[i] == c)
			return (true);
		i++;
	}
	return (false);
}

// t_bool	is_empty_space(char c)
// {
// 	if (c == '\n' || c == ' ' || c == 0) // check if only cases of empty spaces in map - add '\t' ?
// 		return (true);
// 	return (false);
// }
