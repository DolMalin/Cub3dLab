#include "../includes/cub3d.h"


static t_data	*init_data(char *map_file)
{
	t_data	*data;

	(void)map_file;
	data = malloc(sizeof(data));
	if (!data)
		return (NULL);
	
	/*  CHECK BEFORE IF PATH ARE VALID, COLORS ARE VALID, MAP IS VALID */

	/* IMPLEMENT GET_PATH FUNCTION */
	// data->textures_paths = get_textures_paths()

		// data->textures_path[NO] = get_texture_path(map_file, NO);
		// data->textures_path[SO] = get_texture_path(map_file, SO);
		// data->textures_path[WE] = get_texture_path(map_file, WE);
		// data->textures_path[EA] = get_texture_path(map_file, EA);
	

	/* IMPLEMENT GET_COLORS FUNCTION */
	// data->colors[FLOOR] = get_color(map_file, FLOOR);
	// data->colors[CEIL] = get_color(map_file, CEIL);

	/* IMPLEMENT GET_MAP FUNCTION */
	// data->map = get_map(map_file);
	return (data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	// CHECK IF THE INPUT IS VALID
	data = init_data(av[1]);
	if (!data)
	{
		// free_data(data);
		return (1);
	}
	if (!check_input(ac, av))
		return (1);
	
	// free_data(data);
	return (0);
}

