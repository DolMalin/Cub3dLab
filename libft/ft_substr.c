/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:04:32 by aandric           #+#    #+#             */
/*   Updated: 2021/11/17 17:09:13 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	if (!s || start >= (unsigned int)ft_strlen(s))
		return (ft_calloc(1, 1));
	if (ft_strlen(s) > len)
		subs = malloc(sizeof(char) * len + 1);
	else
		subs = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!subs)
		return (0);
	i = 0;
	s = s + start;
	ft_strlcpy(subs, (char *)s, len + 1);
	return (subs);
}
/*
#include <stdio.h>
int main ()
{
	printf("%s\n", ft_substr("HelloHello", 2, 6));
}
*/
