/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:10:07 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/03 15:46:44 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_image	*init_image(t_data *data)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	if (!image)
		error(MEMALLOC);
	image->ptr = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!image->ptr)
		error(MEMALLOC);
	image->addr = mlx_get_data_addr(
			image->ptr,
			&image->bits_per_pixel,
			&image->line_length,
			&image->endian
			);
	if (!image->addr)
		error(MEMALLOC);
	return (image);
}

void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error(MEMALLOC);
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (!data->mlx_win)
		error(MEMALLOC);
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
	free_array((void **)parsed_scene);
	return (data);
}

void	free_data(t_data *data)
{
	free_unterminated_array((void **)data->textures_path, 4);
	free_unterminated_array((void **)data->colors, 2);
	free_array((void **)data->map);
	mlx_destroy_window(data->mlx, data->mlx_win);
	free(data->image->ptr);
	free(data->image->addr);
	free(data->image);
	free(data->player);
	free(data);
}
