/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:46:48 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/10/26 11:51:54 by pdal-mol         ###   ########.fr       */
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
