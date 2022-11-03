/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:49:37 by aandric           #+#    #+#             */
/*   Updated: 2022/11/03 15:38:14 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	rgb_to_hex(unsigned char *rgb)
{
	// return((rgb[R] & 0xff) << 16 | (rgb[G] & 0xff) << 8 | (rgb[B] & 0xff));
	return((rgb[R] << 16 | rgb[G] << 8 | rgb[B]) & 0xff);

	// return ((((int)rgb[R] & 0xff) << 16)
	// 	+ (((int)rgb[G] & 0xff) << 8)
	// 	+ (int)rgb[B] & 0xff);
}
