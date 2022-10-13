#include "../../includes/cub3d.h"

static char	**get_colors_to_check(char **scene)
{
	char	**colors;

	colors = malloc(sizeof(char *) * 2);
	if (!colors)
		return (NULL);
	colors[FLOOR] = get_line_from_key(scene, "F");
	colors[CEIL] = get_line_from_key(scene, "C");
	// printf("ICI\n");
	return (colors);
}

static t_bool	check_color_code(char *color)
{
	char	**split_color;
	int		i;

	split_color = ft_split(color, ',');
	i = 0;
	while (split_color[i])
	{
		if (!ft_strisdigit(split_color[i]))
		{
			free_array((void **)split_color);
			return (false);
		}
		if (!(ft_atoi(split_color[i]) >= 0 && (ft_atoi(split_color[i]) <= 255)))
		{
			free_array((void **)split_color);
			return (false);
		}
		if (!(ft_strlen(split_color[i]) > 3))
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

static int	coma_count(char *color)
{
	int	i;
	int	coma_count;

	i = 0;
	coma_count = 0;
	while (color[i])
	{
		if (color[i] == ',')
			coma_count++;
		i++;
	}
	return (coma_count);
}

static t_bool	check_comas(char **colors)
{
	if (coma_count(colors[CEIL]) != 2)
		return (false);
	if (coma_count(colors[FLOOR]) != 2)
		return (false);
	return (true);
}

t_bool	check_colors(char **scene)
{
	char	**colors;

	colors = get_colors_to_check(scene);
	if (!check_comas(colors))
	{
		free_unterminated_array((void **)colors, 2);
		return (false);
	}
	if (!check_color_code(colors[FLOOR]))
	{
		free_unterminated_array((void **)colors, 2);
		return (false);
	}
	if (!check_color_code(colors[CEIL]))
	{
		free_unterminated_array((void **)colors, 2);
		return (false);
	}
	free_unterminated_array((void **)colors, 2);
	return (true);
}
