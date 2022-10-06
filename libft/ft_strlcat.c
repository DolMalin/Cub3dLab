/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:39:10 by aandric           #+#    #+#             */
/*   Updated: 2022/10/06 15:22:01 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	og_dest_size;

	og_dest_size = ft_strlen(dest);
	if (og_dest_size >= size)
		return (ft_strlen(src) + size);
	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (i < size - 1 && src[j])
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	if (!(size <= 0 || og_dest_size > size))
		dest[i] = '\0';
	return (ft_strlen(src) + og_dest_size);
}
