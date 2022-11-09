/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:04:32 by aandric           #+#    #+#             */
/*   Updated: 2022/11/09 13:39:21 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;

	if (!s || start >= (unsigned int)ft_strlen(s))
		return (ft_calloc(1, 1));
	if (ft_strlen(s) > len)
		subs = malloc(sizeof(char) * len + 1);
	else
		subs = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!subs)
		return (0);
	s = s + start;
	ft_strlcpy(subs, (char *)s, len + 1);
	return (subs);
}
