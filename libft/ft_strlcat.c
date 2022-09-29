/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:39:10 by aandric           #+#    #+#             */
/*   Updated: 2021/11/05 14:45:46 by aandric          ###   ########lyon.fr   */
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

/*
#include <stdio.h>
#include <string.h>
int main()
{
	char dest[12] = "le J c le C";
	char src[15] = " oeoeoeoe";
	printf("%zu\n", ft_strlcat(dest, src, 9));
	printf("%s\n", dest);

	char dest2[12] = "le J c le C";
	char src2[15] = " oeoeoeoe";
	printf("%zu\n", strlcat(dest2, src2, 9));
	printf("%s\n", dest2);
}
*/