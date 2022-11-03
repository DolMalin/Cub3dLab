/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:49:37 by aandric           #+#    #+#             */
/*   Updated: 2022/11/03 13:24:14 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	rgb_to_hex(unsigned char **rgb)
{
	return ((ft_atoi((const char *)rgb[0]) & 0xff) << 16) + (ft_atoi((const char *)rgb[1]) & 0xff << 8) + (ft_atoi((const char *)rgb[2]) & 0xff);
}
