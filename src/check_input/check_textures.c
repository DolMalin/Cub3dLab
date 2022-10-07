#include "../../includes/cub3d.h"

static t_bool   check_texture(char *texture_line)
{
    if (!texture_line)
    {
        printf("No texture found for walls\n");
        return (false);
    }
    if (open(texture_line, O_RDONLY) < 0)
    {
        printf("Can't access the texture file\n");
        return (false);
    }
    return (true);
}

t_bool   check_textures(char **scene)
{
	char	*buffer;
	int		i;

	i = 0;
	while (i < 4)
	{
		if (i == NO)
			buffer = get_line_from_key(scene,"NO");
		else if (i == SO)
			buffer = get_line_from_key(scene,"SO");
		else if (i == WE)
			buffer = get_line_from_key(scene,"WE");
		else if (i == EA)
			buffer = get_line_from_key(scene,"EA");
		if (!buffer)
			return (false);
		if (!check_texture(buffer))
			return (false);
		free(buffer);
		i++;
	}
	return (true);
}
