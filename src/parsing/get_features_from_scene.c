#include "../../includes/cub3d.h"

char	*get_line_from_key(char	**parsed_scene, char *key)
{
	int		i;

	i = 0;
	while(parsed_scene[i])
	{
		if (ft_strncmp(parsed_scene[i], key, ft_strlen(key)) == 0)
		{
			if (parsed_scene[i][0] == 'C' || parsed_scene[i][0] == 'F')
				return (ft_strdup(&parsed_scene[i][1]));
			return (ft_strdup(&parsed_scene[i][2]));
		}
		i++;
	}
	return (NULL);
}

unsigned char	*get_color(char *color_line)
{
	unsigned char	*color;
	char			**seperated_colors;

	seperated_colors = ft_split(color_line, ',');
	if (!seperated_colors)
		return (NULL);
	color = malloc(sizeof(unsigned char) * 3);
	if (!color)
		return (NULL);
	color[R] = (unsigned char)ft_atoi(seperated_colors[0]);
	color[G] = (unsigned char)ft_atoi(seperated_colors[1]);
	color[B] = (unsigned char)ft_atoi(seperated_colors[2]);
	color[4] = '\0';
	free_array((void **)seperated_colors);
	free(color_line);
	return (color);
}

unsigned char	**get_colors(char **parsed_scene)
{
	unsigned char	**colors;

	colors = malloc(sizeof(char *) * 3);
	if (!colors)
		return (NULL);
	colors[FLOOR] = get_color(get_line_from_key(parsed_scene, "F"));
	colors[CEIL] = get_color(get_line_from_key(parsed_scene, "C"));
	colors[2] = 0;
	return (colors);
}

char	**get_textures_paths(char **parsed_scene)
{
	char	**textures_paths;

	textures_paths = malloc(sizeof(char *) * 4);
	if (!textures_paths)
		return (NULL);
	textures_paths[NO] = get_line_from_key(parsed_scene, "NO");
	textures_paths[SO] = get_line_from_key(parsed_scene, "SO");
	textures_paths[WE] = get_line_from_key(parsed_scene, "WE");
	textures_paths[EA] = get_line_from_key(parsed_scene, "EA");
	return (textures_paths);
}

char	**get_map(char	**parsed_scene)
{
	char	**map;
	int		i;
	int		j;
	int		map_len;

	i = 0;
	j = 0;
	map_len = 0;
	while (parsed_scene[i])
	{
		if (!is_config_line(parsed_scene[i]))
			map_len++;
		i++;
	}
	map = malloc(sizeof(char *) * (map_len + 1));
	if (!map)
		return (NULL);
	i = 0;
	while(parsed_scene[i])
	{
		if (!is_config_line(parsed_scene[i]))
		{
			map[j] = trim(parsed_scene[i], "\n");
			if (!map[j])
				return (NULL);
			j++;
		}
		i++;
	}
	map[j] = 0;
	return (map);
}
