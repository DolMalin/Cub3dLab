#include "../../includes/cub3d.h"

void	rotate_left(t_data **data)
{
	(*data)->player->pov -= 1 * ROT_COEF;
}

void	rotate_right(t_data **data)
{
	(*data)->player->pov += 1 * ROT_COEF;
}
