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

// static t_bool	check_config_textures(char **scene)
// {
// 	char	*buffer;
// 	int		i;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		if (i == NO)
// 			buffer = get_line_from_key(scene, "NO");
// 		else if (i == SO)
// 			buffer = get_line_from_key(scene, "SO");
// 		else if (i == EA)
// 			buffer = get_line_from_key(scene, "EA");
// 		else if (i == WE)
// 			buffer = get_line_from_key(scene, "WE");
// 		if (!buffer)
// 			return (false);
// 		i++;
// 		free(buffer);
// 	}
// 	return (true);
// }

t_bool	check_textures(char **scene)
{
	char	*buffer;
	int		i;

	i = 0;
	// if (!check_config_textures(scene))
	// 	return (false);
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
		{
			free(buffer); // do we have to free if null ?
			return (false);
		}
		if (!check_texture(buffer))
		{
			free(buffer);
			return (false);
		}
		free(buffer);
		i++;
	}
	return (true);
}
