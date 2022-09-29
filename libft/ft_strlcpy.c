/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:51:53 by aandric           #+#    #+#             */
/*   Updated: 2021/11/17 16:17:31 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && (i < (dstsize - 1)))
	{
		dst[i] = (char)src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
#include <string.h>
#include <stdio.h>
int main()
{
	char dest[50];
	char src[8] = "Hello";

	printf("%zu\n", ft_strlcpy(dest, src, 0));

	char dest1[50];
	
	printf("%zu", strlcpy(dest1, src, 0));
}
*/