#include "test.h"

int	main(int ac, char **av)
{
	if (ac < 2)
	{
		printf("Error: no path given\n");
		return (0);
	}
	print_data_struct(av[1]);
	return (0);
}
