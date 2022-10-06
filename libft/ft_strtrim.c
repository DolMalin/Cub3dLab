/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:16:53 by aandric           #+#    #+#             */
/*   Updated: 2022/10/06 15:22:17 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;

	if (!s1 || !set)
		return (0);
	start = 0;
	while (s1[start] && ft_strchr((char *)set, s1[start]))
		start++;
	end = ft_strlen(s1);
	if (start == end)
		return (ft_calloc(1, 1));
	end--;
	while (s1[end] && ft_strchr((char *)set, s1[end]))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}
