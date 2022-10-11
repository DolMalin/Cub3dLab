#include "../../includes/cub3d.h"

static t_bool	check_texture(char *texture_path)
{
	size_t	i;

	if (!texture_path)
	{
		printf("Error: no texture found for walls.\n");
		return (false);
	}
	i = ft_strlen(texture_path) - 1;
	while (i && texture_path[i] != '.')
		i--;
	if (ft_strncmp(&texture_path[i], ".xpm", 5) != 0)
	{
		printf("Error: not a .xpm extension for texture.\n");
		return (false);
	}
	if (open(texture_path, O_RDONLY) < 0)
	{
		printf("Error: can't access the texture file\n");
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
			buffer = get_line_from_key(scene, "NO");
		else if (i == SO)
			buffer = get_line_from_key(scene, "SO");
		else if (i == EA)
			buffer = get_line_from_key(scene, "EA");
		else if (i == WE)
			buffer = get_line_from_key(scene, "WE");
		if (!buffer)
			return (false);
		if (!check_texture(buffer))
			return (false);
		free(buffer);
		i++;
	}
	return (true);
}
