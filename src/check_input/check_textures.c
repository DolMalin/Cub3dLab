#include "../../includes/cub3d.h"

static t_bool	check_texture(char *texture_path)
{
	size_t	i;

	if (!texture_path)
		return (false);
	i = ft_strlen(texture_path) - 1;
	while (i && texture_path[i] != '.')
		i--;
	if (ft_strncmp(&texture_path[i], ".xpm", 5) != 0)
		return (false);
	if (open(texture_path, O_RDONLY) < 0)
	{
		// close
		return (false);
	}
	return (true);
}

t_bool	check_textures(char **scene)
{
	char	*buffer;
	int		i;

	i = 0;
	while (i < 4)
	{
		if (i == NO)
			{
			buffer = get_line_from_key(scene, "NO");
			}
		else if (i == SO)
			buffer = get_line_from_key(scene, "SO");
		else if (i == EA)
		{
			buffer = get_line_from_key(scene, "EA");
			printf("yo from EA\n");
			printf("buffer ==%s\n", buffer);
		}
		else if (i == WE)
			buffer = get_line_from_key(scene, "WE");
		if (!buffer)
		{

			printf("YO jdevrais passer par la\n");
			free(buffer);
			return (false);
		}
		if (!check_texture(buffer))
		{
			//printf("YO\n");
			return (false);
		}
		printf("buffer == %s\n", buffer);
		free(buffer);
		i++;
	}
	return (true);
}
