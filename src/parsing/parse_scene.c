#include "../../includes/cub3d.h"

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
	trimed_scene = malloc(sizeof(char *) * (array_len((void **)parsed_scene) + 1));
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
	trimed_scene[i] = '\0';
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