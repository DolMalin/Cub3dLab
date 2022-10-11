#include "../includes/cub3d.h"

t_bool	error(int error_id, char **array)
{	
	if (error_id == MAP_NOT_CLOSED)
		printf("Error: map is not closed.\n");
	else if  (error_id == INVALID_CHARS)
		printf("Error: invalid characters in the map.\n");
	else if (error_id == INVALID_MAP_LEN)
		printf("Error: invalid map lenght.\n");
	else if (error_id == COLOR_OVERFLOW)
		printf("Error: color code must be between 0 and 255.\n");
	else if (error_id == COLOR_INV_CHARS)
		printf("Error: color code contains invalid characters.\n");
	else if (error_id == COLOR_RGB)
		printf("Error: color code must be composed of 3 colors RGB.\n");
	else if (error_id == COLOR_COMA_COUNT)
		printf("Error: check comas in color code.\n");
	free_array((void **)array);
	return (false);
}
