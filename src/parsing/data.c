/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:10:07 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/10/17 15:10:52 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
}

void	update_player_pos(t_data **data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while ((*data)->map[i])
	{
		j = 0;
		while ((*data)->map[i][j])
		{
			if (is_in_charset((*data)->map[i][j], "NSEW"))
			{
				(*data)->y = i;
				(*data)->x = j;
			}
			j++;
		}
		i++;
	}
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
	data->image = create_image(data);
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
