/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:10:07 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/09 13:25:04 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_ray	*create_ray(void)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		error(MEMALLOC);
	return (ray);
}

t_data	*init_data(char *scene_file)
{
	t_data	*data;
	char	**parsed_scene;

	data = malloc(sizeof(t_data));
	if (!data)
		error(MEMALLOC);
	parsed_scene = parse_scene_file(scene_file);
	if (!parsed_scene)
		return (NULL);
	data->textures_path = get_textures_paths(parsed_scene);
	data->colors = get_colors(parsed_scene);
	data->color_ceil = rgb_to_hex(data->colors[CEIL]);
	data->color_floor = rgb_to_hex(data->colors[FLOOR]);
	data->map = get_map(parsed_scene);
	init_window(data);
	data->player = init_player(data);
	data->image = init_image(data);
	data->textures = init_textures(data, data->textures_path);
	data->y_max = array_len((void **)data->map);
	data->precomputed = init_precomputed(data);
	data->ray_horizontal = create_ray();
	data->ray_vertical = create_ray();
	free_array((void **)parsed_scene);
	return (data);
}

void	free_data(t_data *data)
{
	free_unterminated_array((void **)data->textures_path, 4);
	free_unterminated_array((void **)data->textures, 4);
	free_unterminated_array((void **)data->colors, 2);
	free_array((void **)data->map);
	mlx_destroy_window(data->mlx, data->mlx_win);
	free(data->image->ptr);
	free(data->image->addr);
	free(data->image);
	free(data->player);
	free(data->ray_horizontal);
	free(data->ray_vertical);
	free(data->precomputed->map_lines_len);
	free(data->precomputed);
	free(data);
}
