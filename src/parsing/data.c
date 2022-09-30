#include "../../includes/cub3d.h"

t_data	*init_data(char *scene_file)
{
	t_data	*data;
	char	**parsed_scene;

	data = malloc(sizeof(data));
	if (!data)
		return (NULL);
	parsed_scene = parse_scene_file(scene_file);
	if (!parsed_scene)
		return (NULL);
	data->textures_path = get_textures_paths(parsed_scene);
	data->colors = get_colors(parsed_scene);

	/*  CHECK BEFORE IF PATH ARE VALID, COLORS ARE VALID, scene IS VALID */;

	/* IMPLEMENT GET_scene FUNCTION */
	// data->scene = get_scene(scene_file);
	free_array((void **)parsed_scene);
	return (data);
}

void	free_data(t_data *data)
{
	free_array((void **)data->textures_path);
	// free_array((void **)data->colors);
}
