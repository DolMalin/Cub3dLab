#include "../includes/cub3d.h"

t_bool	error(int error_id, char **array)
{	
	if (error_id == MAP_NOT_CLOSED)
		printf("Error: map is not closed\n");
	if  (error_id == INVALID_CHARS)
		printf("Error: invalid characters in the map\n");
	if (error_id == INVALID_MAP_LEN)
		printf("Error: invalid map lenght.\n");
	free_array((void **)array);
	return (false);
}
