/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:44:38 by aandric           #+#    #+#             */
/*   Updated: 2021/11/09 19:04:30 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (ft_strlen(needle) <= 0)
		return ((char *)haystack);
	i = 0;
	j = 0;
	while (haystack[i] && i < len)
	{
		k = i;
		j = 0;
		while (haystack[k] == needle[j] && k < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			k++;
			j++;
		}
		i++;
	}
	return (0);
}

/*
#include <string.h>
#include <stdio.h>
int main ()
{
	printf("%s\n", ft_strnstr("FF", "see F your F return F now F", 15));
	printf("%s\n", strnstr("FF", "see F your F return F now F", 15));
}
*/