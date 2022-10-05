#include "test.h"

int	main(int ac, char **av)
{
	if (!check_input(ac, av))
	{
		printf("Error\n");
		return (1);
	}
	return (0);
}
