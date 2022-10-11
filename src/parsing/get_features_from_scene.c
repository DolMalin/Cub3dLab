#include "../../includes/cub3d.h"

char	*get_line_from_key(char **parsed_scene, char *key)
{
	int		i;

	i = 0;
	while (parsed_scene[i])
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

unsigned char	*get_color(char *line)
{
	unsigned char	*color;
	char			**splited_line;

	splited_line = ft_split(line, ',');
	if (!splited_line)
		return (NULL);
	color = malloc(sizeof(unsigned char) * 3);
	if (!color)
		return (NULL);
	color[R] = (unsigned char)ft_atoi(splited_line[0]);
	color[G] = (unsigned char)ft_atoi(splited_line[1]);
	color[B] = (unsigned char)ft_atoi(splited_line[2]);
	free_array((void **)splited_line);
	free(line);
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
	textures_paths[EA] = get_line_from_key(parsed_scene, "EA");
	textures_paths[WE] = get_line_from_key(parsed_scene, "WE");
	return (textures_paths);
}

char	**get_map(char **parsed_scene)
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
	//printf("\tmap_len: %d\n", map_len);
	map = malloc(sizeof(char *) * (map_len + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (parsed_scene[i])
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
