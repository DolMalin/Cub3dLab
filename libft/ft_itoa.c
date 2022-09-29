/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:32:44 by aandric           #+#    #+#             */
/*   Updated: 2021/11/16 19:01:52 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_nb(long int nb)
{
	long int	i;

	i = 1;
	if (nb < 0)
	{
		nb *= -1;
		i++;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nb)
{
	int			len;
	char		*tab;
	long int	nbr;

	nbr = (long int)nb;
	len = ft_len_nb(nbr);
	tab = malloc(sizeof(char) * len + 1);
	if (!tab)
		return (NULL);
	if (nbr < 0)
	{
		nbr *= -1;
		tab[0] = '-';
	}
	tab[len] = '\0';
	len--;
	if (nb == 0)
		tab[len] = '0';
	while (nbr > 0)
	{
		tab[len] = nbr % 10 + '0';
		nbr = nbr / 10;
		len--;
	}
	return (tab);
}
/*
#include <stdio.h>
int	main()
{
	printf("%s\n", ft_itoa(-2147483648));
}
*/