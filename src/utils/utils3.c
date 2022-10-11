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
