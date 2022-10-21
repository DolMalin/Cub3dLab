#include "../../includes/cub3d.h"

char    get_player_token(t_data *data)
{
    size_t	i;
	size_t	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (is_in_charset(data->map[i][j], "NSEW"))
			{
                if (is_in_charset(data->map[i][j], "N"))
                    return ('N');
                else if (is_in_charset(data->map[i][j], "S"))
                    return ('S');
                else if (is_in_charset(data->map[i][j], "E"))
                    return ('E');
                return ('W');
			}
			j++;
		}
		i++;
	}
    return (0);
}

void	rotate_right(t_data **data)
{
	(*data)->player->pov -= ROT_COEF;
	if ((*data)->player->pov <= 0)
		(*data)->player->pov = (2 * M_PI - (ROT_COEF));
	(*data)->player->ray_coef_x = cos((*data)->player->pov);
	(*data)->player->ray_coef_y = sin((*data)->player->pov);

}

void	rotate_left(t_data **data)
{
	(*data)->player->pov += ROT_COEF;
	if ((*data)->player->pov >= 2 * M_PI)
		(*data)->player->pov -= (2 * M_PI);
	(*data)->player->ray_coef_x = sin((*data)->player->pov);
	(*data)->player->ray_coef_y = cos((*data)->player->pov);
}
