#include "test.h"

void	print_data_struct(char *path)
{
	t_data	*data;
	int		fd;

	fd = open(path, O_RDONLY);
	if (!fd)
	{
		printf("Error: path %s is not valid\n", path);
		return ;
	}
	
	data = init_data(path);
	if (!data)
		return;
	printf("%s\n", data->textures_path[NO]);
	printf("%s\n", data->textures_path[SO]);
	printf("%s\n", data->textures_path[WE]);
	printf("%s\n", data->textures_path[EA]);
	printf("%d,%d,%d\n", data->colors[FLOOR][R], data->colors[FLOOR][G], data->colors[FLOOR][B]);
	printf("%d,%d,%d\n", data->colors[CEIL][R], data->colors[CEIL][G], data->colors[CEIL][B]);
	free_data(data);
	return ;
}
