/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:10:07 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/10/18 11:57:03 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_image	*init_image(t_data *data)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	image->ptr = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	image->addr =mlx_get_data_addr(image->ptr, &image->bits_per_pixel, &image->line_length, &image->endian);
	return (image); 
}

// void	get_player_pov(t_data **data)
// {
// 	char		player_pov;
// 	player_pov = get_player_token(data);
// 	if (player_pov == 'N')
// 		player->pov = M_PI_2;
// 	if (player_pov == 'S')
// 		player->pov = 3 * M_PI_2;
// 	if (player_pov == 'E')
// 		player->pov = M_PI;
// 	if (player_pov == 'W')
// 		player->pov = 0;
	
					
// }

// t_player	*init_player(t_data *data)
// {
// 	t_player	*player;
// 	size_t		i;
// 	size_t		j;

	
// 	i = 0;
// 	get_player_pos(&data);
	
// 	while (data->map[i])
// 	{
// 		j = 0;
// 		while (data->map[i][j])
// 		{
// 			if (is_in_charset(data->map[i][j], "NSEW"))
// 			{
// 				player->y = i;
// 				player->x = j; // modify with float value
				
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (player);
// }

void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
}

t_data	*init_data(char *scene_file)
{
	t_data	*data;
	char	**parsed_scene;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	parsed_scene = parse_scene_file(scene_file);
	if (!parsed_scene)
		return (NULL);
	data->textures_path = get_textures_paths(parsed_scene);
	data->colors = get_colors(parsed_scene);
	data->map = get_map(parsed_scene);
	init_window(data);
	data->image = init_image(data); // if data image null secure it
	free_array((void **)parsed_scene);
	return (data);
}

void	free_data(t_data *data)
{
	free_unterminated_array((void **)data->colors, 2);
	free_unterminated_array((void **)data->textures_path, 4);
	free_array((void **)data->map);
	free(data);
}
