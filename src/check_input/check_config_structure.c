#include "../../includes/cub3d.h"

static t_bool	check_config_textures(char **scene)
{
	char	*buffer;
	int		i;

	i = 0;
	while (i < 4)
	{
		//print_map(scene);
		if (i == NO)
			buffer = get_line_from_key(scene, "NO");
		else if (i == SO)
			buffer = get_line_from_key(scene, "SO");
		else if (i == EA)
			buffer = get_line_from_key(scene, "EA");
		else if (i == WE)
			buffer = get_line_from_key(scene, "WE");
		if (!buffer)
			{printf("\tYOOOOO\n");
			return (false);}
		i++;
		free(buffer);
	}
	return (true);
}

static t_bool	check_line_color(char **scene)
{
	char	*buffer;
	int		i;

	i = 0;
	while (i < 2)
	{
		if (i == FLOOR)
			buffer = get_line_from_key(scene, "F");
		else if (i == CEIL)
			buffer = get_line_from_key(scene, "C");
		if (!buffer)
			return (false);
		free(buffer);
		i++;
	}
	return (true);
}

static t_bool	check_config_line_missing(char **scene)
{
	if (!check_config_textures(scene))
		return (false);
	if (!check_line_color(scene))
		return (false);
	return (true);
}

static t_bool	check_structure(char **scene)
{
	int	i;

	i = 0;
	while (is_config_line(scene[i]) && scene[i])
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
	if (!check_config_line_missing(scene))
		return (false);
	if (!check_structure(scene))
		return (false);
	return (true);
}
