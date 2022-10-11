#include "../../includes/cub3d.h"

static char	**get_colors_to_check(char **scene)
{
	char	**colors;

	colors = malloc(sizeof(char *) * 4);
	if (!colors)
		return (NULL);
	colors[FLOOR] = get_line_from_key(scene, "F");
	colors[CEIL] = get_line_from_key(scene, "C");
	colors[2] = 0;
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
			return (error(COLOR_INV_CHARS, split_color));
		if (!(ft_atoi(split_color[i]) >= 0 && (ft_atoi(split_color[i]) <= 255)))
			return (error(COLOR_OVERFLOW, split_color));
		i++;
	}
	if (i != 3)
		return (error(COLOR_RGB, split_color));
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
		return (error(COLOR_COMA_COUNT, colors));
	if (coma_count(colors[FLOOR]) != 2)
		return (error(COLOR_COMA_COUNT, colors));
	return (true);
}

t_bool	check_colors(char **scene)
{
	char	**colors;

	colors = get_colors_to_check(scene);
	if (!check_comas(colors))
		return (false);
	if (!check_color_code(colors[FLOOR]))
		return (false);
	if (!check_color_code(colors[CEIL]))
		return (false);
	free_array((void **)colors);
	return (true);
}
