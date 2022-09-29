#include "../includes/cub3d.h"

t_data	*init_data(char *map_file)
{
	t_data	*data;

	data = malloc(sizeof(data));
	if (!data)
		return (NULL);
	/*  CHECK BEFORE IF PATH ARE VALID, COLORS ARE VALID, MAP IS VALID */

	/* IMPLEMENT GET_PATH FUNCTION */
	// data->no_path = get_path(map_file, NO);
	// data->so_path = get_path(map_file, SO);
	// data->we_path = get_path(map_file, WE);
	// data->ea_path = get_path(map_file, EA);

	/* IMPLEMENT GET_COLOR FUNCTION */
	// data->floor_color = get_color(map_file, FLOOR);
	// data->ceil_color = get_color(map_file, CEIL);

	/* IMPLEMENT GET_MAP FUNCTION */
	// data->map = get_map(map_file);
	return (data);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_data	*data;

	// CHECK IF THE INPUT IS VALID
	data = init_data(av[1]);
	if (!data)
	{
		// free_data(data);
		return (0);
	}

	// free_data(data);
	return (0);
}

