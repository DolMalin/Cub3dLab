/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:39:06 by aandric           #+#    #+#             */
/*   Updated: 2022/02/24 14:25:00 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_chrn(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_len_to_malloc(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
	{
		j++;
		if (s2[j] == '\n')
		{	
			j++;
			break ;
		}				
	}
	return (i + j);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	s3 = malloc(sizeof(char) * (ft_len_to_malloc(s1, s2) + 1));
	if (!s3)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		s3[i] = s1[i];
	if (s1)
		free(s1);
	while (s2[j])
	{
		s3[i++] = s2[j++];
		if (s2[j - 1] == '\n')
			break ;
	}
	s3[i] = '\0';
	return (s3);
}
