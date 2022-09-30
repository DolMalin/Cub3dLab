#include "../includes/cub3d.h"

int	check_input(int ac, char **av)
{
	if (ac < 2)
	{
		printf("Please select a scene in arguments");
		return (0);
	}
	if (open(av[1], O_RDONLY) < 0)
	{
		printf("Unreadable scene file");
		return (0);
	}
	return (1);
}