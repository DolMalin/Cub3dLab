#include "../../includes/cub3d.h"

char	*trim(char *line, char *charset)
{
	char	*trimed_line;
	int		i;
	int		s_count;
	int		k;

	i = 0;
	s_count = 0;
	while (line[i])
	{
		if (!is_in_charset(line[i], charset))
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
	while (line[i])
	{
		if (!is_in_charset(line[i], charset))
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
	trimed_scene = malloc(sizeof(char *)
			* (array_len((void **)parsed_scene) + 1));
	if (!trimed_scene)
		return (NULL);
	while (parsed_scene[i])
	{
		if (is_config_line(parsed_scene[i]))
			trimed_scene[i] = trim(parsed_scene[i], " \n\t");
		else
			trimed_scene[i] = ft_strdup(parsed_scene[i]);
		free(parsed_scene[i]);
		i++;
	}
	trimed_scene[i] = 0; // verifier taille tableau on envoie derniere ligne nulle dans trim
	free(parsed_scene);
	return (trimed_scene);
}

char	**remove_empty_lines(char	**parsed_scene)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	**output;

	i = 0;
	j = 0;
	len = 0;
	while (parsed_scene[i])
	{
		if (!is_empty_line(parsed_scene[i]))
			len++;
		i++;
	}
	output = malloc(sizeof(char *) * (len + 1));
	if (!output)
		return (NULL);
	i = 0;
	while (parsed_scene[i])
	{
		if (!is_empty_line(parsed_scene[i]))
		{
			output[j] = ft_strdup(parsed_scene[i]);
			j++;
		}
		i++;
	}
	output[j] = 0;
	free_array((void **)parsed_scene);
	return (output);
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
	while (parsed_scene[i])
	{
		i++;
		parsed_scene[i] = get_next_line(fd);
	}
	parsed_scene[i] = NULL;
	parsed_scene = remove_empty_lines(parsed_scene);
	parsed_scene = trim_config_line(parsed_scene);
	if (!parsed_scene)
		return (NULL);
	return (parsed_scene);
}
