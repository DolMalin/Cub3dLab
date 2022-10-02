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

	/*  CHECK BEFORE IF PATH ARE VALID, COLORS ARE VALID, scene IS VALID */;

	/* IMPLEMENT GET_scene FUNCTION */
	// data->scene = get_scene(scene_file);
	free_array((void **)parsed_scene);
	return (data);
}

void	free_unterminated_array(void **array, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		return ;
	while (i < n)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_data(t_data *data)
{
	// // free_unterminated_array((void **)data->colors[FLOOR], 3);
	// free(data->colors[FLOOR]);
	// free(data->colors[CEIL]);
	// free(data->colors);
	free_unterminated_array((void **)data->colors, 2);
	free_unterminated_array((void **)data->textures_path, 4);
	free(data);

}
