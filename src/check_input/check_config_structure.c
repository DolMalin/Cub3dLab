#include "../../includes/cub3d.h"

t_bool	str_is_in_charset(char *str, char *charset)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!is_in_charset(str[i], charset))
			return (false);
		i++;
	}
	return (true);
}
static t_bool	check_structure(char **scene)
{
	int	i;

	i = 0;
	while (is_config_line(scene[i]) || str_is_in_charset(scene[i], " \n"))
		i++;
	while (scene[i])
	{
		if (is_config_line(scene[i]))
			return (false);
		i++;
	}
	return (true);
}

t_bool	check_config_structure(char **scene)
{
	if (!check_structure(scene))
		return (false);
	return (true);
}
