/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:51:06 by aandric           #+#    #+#             */
/*   Updated: 2022/11/09 13:39:54 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s2;

	if (!s1)
		return (NULL);
	s2 = malloc(sizeof(const char) * ft_strlen(s1) + 1);
	if (!s2)
		return (0);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*s2;

	if (!s1 || n < 1)
		return (NULL);
	s2 = malloc(sizeof(const char) * ft_strlen(s1) + 1);
	if (!s2)
		return (0);
	i = 0;
	while (s1[i] && i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
