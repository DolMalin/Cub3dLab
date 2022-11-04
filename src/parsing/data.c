/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:10:07 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/04 18:08:35 by pdal-mol         ###   ########.fr       */
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

t_texture	*init_texture(t_data *data, char *texture_path)
{
	t_texture	*texture;

	(void)data;
	(void)texture_path;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		error(MEMALLOC);
	texture->width = 100;
	texture->height = 100;
	texture->ptr = mlx_xpm_file_to_image(data->mlx, texture_path, &texture->width, &texture->height);
	if (!texture->ptr)
		error(MEMALLOC);
	texture->addr = mlx_get_data_addr(
			texture->ptr,
			&texture->bits_per_pixel,
			&texture->line_length,
			&texture->endian
			);
	if (!texture->addr)
		error(MEMALLOC);
	return (texture);
}

t_texture **init_textures(t_data *data, char **textures_path)
{
	t_texture **textures;
	// (void)data;
	// (void)textures_path;
	textures = malloc(sizeof(t_texture *) * 4);
	if (!textures)
		error(MEMALLOC);
	textures[NO] = init_texture(data, textures_path[NO]);
	textures[SO] = init_texture(data, textures_path[SO]);
	textures[EA] = init_texture(data, textures_path[EA]);
	textures[WE] = init_texture(data, textures_path[WE]);
	return (textures);
}

t_precomputed	*init_precomputed(t_data *data)
{
	t_precomputed	*precomputed;

	(void)data;

	precomputed = malloc(sizeof(precomputed));
	if (!precomputed)
		error(MEMALLOC);
	precomputed->float_line = FLOAT_LINE;
	precomputed->fov_amplitude = FOV_AMPLITUDE;
	precomputed->stripe = STRIPE;
	precomputed->radians[PI_ON_SIX] = M_PI / 6;
	precomputed->radians[PI_ON_FOUR] = M_PI / 4;
	precomputed->radians[PI_ON_THREE] = M_PI / 3;
	precomputed->radians[PI_ON_TWO] = M_PI / 2;
	precomputed->radians[TWO_PI_ON_THREE] =  2 * M_PI / 3;
	precomputed->radians[THREE_PI_ON_FOUR] =  3 * M_PI / 4;
	precomputed->radians[FIVE_PI_ON_SIX] =  5 * M_PI / 6;
	precomputed->radians[PI] = M_PI;
	precomputed->radians[SEVEN_PI_ON_SIX] =  7 * M_PI / 6;
	precomputed->radians[FIVE_PI_ON_FOUR] =  5 * M_PI / 4;
	precomputed->radians[FOUR_PI_ON_THREE] =  4 * M_PI / 3;
	precomputed->radians[THREE_PI_ON_TWO] =  3 * M_PI / 2;	
	precomputed->radians[FIVE_PI_ON_THREE] =  5 * M_PI / 3;
	precomputed->radians[SEVEN_PI_ON_FOUR] =  7 * M_PI / 4;
	precomputed->radians[ELEVEN_PI_ON_SIX] =  11 * M_PI / 6;	
	precomputed->radians[TWO_PI] = 2 * M_PI;

	return (precomputed);
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
	data->precomputed = init_precomputed(data);
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
