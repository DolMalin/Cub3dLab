#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	//t_data	*data;
	(void)ac;

	// CHECK IF THE INPUT IS VALID
	if (!check_input(ac, av))
		return (1);
	//data = init_data(av[1]);
	/*if (!data)
	{
		// free_data(data);
		return (1);
	}
	printf("%s\n", data->textures_path[NO]);
	printf("%s\n", data->textures_path[SO]);
	printf("%s\n", data->textures_path[WE]);
	printf("%s\n", data->textures_path[EA]);
	printf("%d %d %d\n", data->colors[FLOOR][R], data->colors[FLOOR][G], data->colors[FLOOR][B]);
	printf("%d %d %d\n", data->colors[CEIL][R], data->colors[CEIL][G], data->colors[CEIL][B]);
	free_data(data);*/
	return (0);
}

