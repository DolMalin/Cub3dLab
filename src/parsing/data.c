#include "../../includes/cub3d.h"

t_data	*init_data(char *scene_file)
{
	t_data	*data;
	char	**parsed_scene;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	parsed_scene = parse_scene_file(scene_file);
	if (!parsed_scene)
		return (NULL);
	data->textures_path = get_textures_paths(parsed_scene);
	data->colors = get_colors(parsed_scene);
	data->map = get_map(parsed_scene);
	free_array((void **)parsed_scene);
	return (data);
}

void	free_data(t_data *data)
{
	free_unterminated_array((void **)data->colors, 2);
	free_unterminated_array((void **)data->textures_path, 4);
	free_array((void **)data->map);
	free(data);
}
