/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:46:48 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/04 15:14:13 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * image->line_length + x * (image->bits_per_pixel / 8));
	dst = image->addr + offset;
	*(unsigned int *)dst = color;
}

void	print_bigger(t_image *image, float x, float y, int color_code)
{
	int		i;
	int		j;
	float	x_pos;
	float	y_pos;

	i = 0;
	while (i < PRINT_COEF)
	{
		j = 0;
		while (j < PRINT_COEF)
		{
			x_pos = (x * PRINT_COEF) + i + 20;
			y_pos = (y * PRINT_COEF) + j + 20;
			my_mlx_pixel_put(image, x_pos, y_pos, color_code);
			j++;
		}
		i++;
	}
}

void	draw_line(t_data *data, float end_x, float end_y)
{
	float	delta_x;
	float	delta_y;
	int		pixels;
	float	pixel_x;
	float	pixel_y;

	delta_x = end_x - data->player->x;
	delta_y = end_y - data->player->y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y)) * PRINT_COEF + 20;
	delta_x = delta_x / pixels;
	delta_y = delta_y / pixels;
	pixel_x = data->player->x;
	pixel_y = data->player->y;
	while (pixels)
	{
		if (pixels == 1)
			my_mlx_pixel_put(data->image, pixel_x * PRINT_COEF + 20,
				pixel_y * PRINT_COEF + 20, 0xfffff);
		else
			my_mlx_pixel_put(data->image, pixel_x * PRINT_COEF + 20,
				pixel_y * PRINT_COEF + 20, 0x0D062B);
		pixel_x += delta_x;
		pixel_y += delta_y;
		pixels--;
	}
}


