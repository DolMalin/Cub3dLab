#include "../../includes/cub3d.h"

t_bool	check_arguments(int ac, char **av)
{
	if (ac < 2)
	{
		printf("Please select a scene in arguments");
		return (0);
	}
	if (!ft_strnstr(av[1], ".cub", ft_strlen(av[1])))
	{
		printf("Not a .cub scene");
		return (0);
	}
	if (open(av[1], O_RDONLY) < 0)
	{
		printf("Can't access scene file");
		return (0);
	}
	return (1);
}



t_bool	check_input(int ac, char **av)
{
	if (!check_arguments(ac, av))
		return (0);
	

}