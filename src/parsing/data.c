/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:10:07 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/10/13 18:04:14 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, 1920, 1080, "CUB3D");
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
