#include "../../includes/cub3d.h"

static t_bool	check_rgb_range(char *color)
{
	if (!(ft_atoi(color) >= 0 && (ft_atoi(color) <= 255)))
		return (false);
	return (true);
}

t_bool	check_color_code(char *color)
{
	char	**split_color;
	int		i;

	split_color = ft_split(color, ',');
	i = 0;
	while (split_color[i])
	{
		if (ft_strlen(split_color[i]) > 3 || !ft_strisdigit(split_color[i])
			|| !check_rgb_range(split_color[i]))
		{
			free_array((void **)split_color);
			return (false);
		}
		i++;
	}
	if (i != 3)
	{
		free_array((void **)split_color);
		return (false);
	}
	free_array((void **)split_color);
	return (true);
}
