#include "../includes/cub3d.h"

void	error(char *error_msg, void **array)
{	
	printf("%s", error_msg);
	free_array((void **)array);
	exit(EXIT_FAILURE);
}
