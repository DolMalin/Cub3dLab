#include "../../includes/cub3d.h"

char	*get_line_from_key(char	**parsed_scene, char *key)
{
	int		i;

	i = 0;
	while(parsed_scene[i])
	{
		if (ft_strncmp(parsed_scene[i], key, ft_strlen(key)) == 0)
			return (ft_strdup(parsed_scene[i]));
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
	color[R] = (unsigned char)ft_atoi(&splited_line[0][1]);
	color[G] = (unsigned char)ft_atoi(splited_line[1]);
	color[B] = (unsigned char)ft_atoi(splited_line[2]);
	free_array((void **)splited_line);
	free(line);
	return (color);
}

unsigned char	**get_colors(char **parsed_scene)
{
	unsigned char	**colors;

	colors = malloc(sizeof(unsigned char *));
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
	textures_paths[WE] = get_line_from_key(parsed_scene, "WE");
	textures_paths[EA] = get_line_from_key(parsed_scene, "EA");
	return (textures_paths);
}

char	*trim_spaces(char	*line)
{
	char 	*trimed_line;
	int		i;
	int		s_count;
	int		k;

	i = 0;
	s_count = 0;
	while(line[i])
	{
		if (line[i] != ' ')
			s_count++;
		i++;
	}
	if (s_count == 0)
		return (NULL);
	trimed_line = malloc(sizeof(char) * (s_count + 1));
	if (!trimed_line)
		return (NULL);
	i = 0;
	k = 0;
	while(line[i])
	{
		if (line[i] != ' ')
		{
			trimed_line[k] = line[i];
			k++;
		}
		i++;
	}
	trimed_line[k] = '\0';
	return (trimed_line);
}

char	**trim_config_line(char **parsed_scene)
{
	char	**trimed_scene;
	int		i;

	i = 0;
	trimed_scene = malloc(sizeof(char *) * array_len((void **)parsed_scene));
	if (!trimed_scene)
		return (NULL);
	while(parsed_scene[i])
	{
		if (is_config_line(parsed_scene[i]))
			trimed_scene[i] = trim_spaces(parsed_scene[i]);
		else
			trimed_scene[i] = ft_strdup(parsed_scene[i]);
		free(parsed_scene[i]);
		i++;
	}
	free(parsed_scene);
	return (trimed_scene);
}

char	**parse_scene_file(char *scene_file)
{
	char	**parsed_scene;
	int		i;
	int		fd;

	i = 0;
	fd = open(scene_file, O_RDONLY);
	parsed_scene = malloc(sizeof(char *) * (lines_count(scene_file) + 1));
	if (!parsed_scene)
		return (NULL);
	parsed_scene[i] = get_next_line(fd);
	while(parsed_scene[i])
	{
		i++;
		parsed_scene[i] = get_next_line(fd);
	}
	parsed_scene[i] = 0;
	parsed_scene = trim_config_line(parsed_scene);
	if (!parsed_scene)
		return (NULL);
	return (parsed_scene);
}

