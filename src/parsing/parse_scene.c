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
	color[R] = (unsigned char)ft_atoi(&splited_line[0][2]);
	color[G] = (unsigned char)ft_atoi(splited_line[1]);
	color[B] = (unsigned char)ft_atoi(splited_line[2]);
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
	textures_paths[EA] = get_line_from_key(parsed_scene, "EA"); // check if path is right : after "NO", "SO" etc
	return (textures_paths);
}

char	**parse_scene_file(char *scene_file)
{
	char	**parsed_scene_file;
	int		i;
	int		fd;

	i = 0;
	fd = open(scene_file, O_RDONLY);
	parsed_scene_file = malloc(sizeof(char *) * (lines_count(scene_file) + 1));
	parsed_scene_file[i] = get_next_line(fd);
	while(parsed_scene_file[i])
	{
		i++;
		parsed_scene_file[i] = get_next_line(fd);
	}
	parsed_scene_file[i] = 0;
	// TRIM SPACES
	
	return (parsed_scene_file);
}

