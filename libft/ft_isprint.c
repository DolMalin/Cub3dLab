/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:18:32 by aandric           #+#    #+#             */
/*   Updated: 2021/11/06 15:26:45 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	return ((c > 31 && c < 127));
}
/*
#include <stdio.h>
#include <ctype.h>
int main ()
{
	printf("%d\n", ft_isprint(127));
	printf("%d\n", isprint(127));
}
*/