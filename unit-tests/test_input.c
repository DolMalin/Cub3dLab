#include "test.h"

int	main(int ac, char **av)
{
	if (!check_input(ac, av))
		return (1);
	printf("Test OK");
	return (0);
}