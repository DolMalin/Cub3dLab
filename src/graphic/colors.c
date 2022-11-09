/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:49:37 by aandric           #+#    #+#             */
/*   Updated: 2022/11/09 12:40:48 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	rgb_to_hex(unsigned char *rgb)
{
	return (rgb[R] << 16 | rgb[G] << 8 | rgb[B]);
}

int	ft_get_color_from_texture(t_texture *texture, int x, int y)
{
	if (x > texture->width || y > texture->height || x < 0 || y < 0)
		return (0x0);
	return (*(int *)(texture->addr
		+ (y * texture->line_length + x * texture->bits_per_pixel / 8))
	);
}
