/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:14:22 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/11 17:39:43 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_image	*init_image(t_data *data)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	if (!image)
		error(MEMALLOC);
	image->ptr = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!image->ptr)
		error(MLX);
	image->addr = mlx_get_data_addr(
			image->ptr,
			&image->bits_per_pixel,
			&image->line_length,
			&image->endian
			);
	if (!image->addr)
		error(MLX);
	return (image);
}

void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error(MLX);
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (!data->mlx_win)
		error(MLX);
}

t_texture	*init_texture(t_data *data, char *texture_path)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		error(MEMALLOC);
	texture->ptr = mlx_xpm_file_to_image(data->mlx, texture_path,
			&texture->width, &texture->height);
	if (!texture->ptr)
		error(MLX);
	texture->addr = mlx_get_data_addr(
			texture->ptr,
			&texture->bits_per_pixel,
			&texture->line_length,
			&texture->endian
			);
	if (!texture->addr)
		error(MLX);
	return (texture);
}

t_texture	**init_textures(t_data *data, char **textures_path)
{
	t_texture	**textures;

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
	int				i;

	i = 0;
	precomputed = malloc(sizeof(t_precomputed));
	if (!precomputed)
		error(MEMALLOC);
	precomputed->float_line = (float)(WIN_HEIGHT * 0.5);
	precomputed->fov_amplitude = (float)(FOV * FOV_STEP * 0.5);
	precomputed->stripe = WIN_WIDTH / RAYS;
	precomputed->map_lines_len = malloc(sizeof(int) * (data->y_max + 1));
	if (!precomputed->map_lines_len)
		error(MEMALLOC);
	while (i < data->y_max)
	{
		precomputed->map_lines_len[i] = ft_strlen(data->map[i]);
		i++;
	}
	precomputed->map_lines_len[i] = 0;
	return (precomputed);
}
