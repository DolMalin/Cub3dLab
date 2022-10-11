#include "../includes/cub3d.h"

t_bool	error(int error_id, char **scene)
{	
	if (error_id == MAP_NOT_CLOSED)
		printf("Error: map is not closed\n");
	if  (error_id == INVALID_CHARS)
		printf("Error: invalid characters in the map\n");
	free_array((void **)scene);
	return (false);
}
