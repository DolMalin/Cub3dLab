/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 19:30:26 by aandric           #+#    #+#             */
/*   Updated: 2021/11/09 13:53:43 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	if (!dest && !src)
		return (0);
	else if (d > s)
		while (n-- > 0)
			d[n] = s[n];
	else
		return (ft_memcpy(d, s, n));
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int main() {

    int array [] = {54, 12, 41, 65, 32};
    int * copy = NULL;
    int length = sizeof(int) * 5;

    copy = (int *) malloc( length );
    ft_memmove( copy, array, length);
        
    for( length=0; length<5; length++ ) {
        printf( "%d ", copy[ length ] );
    }
    printf("\n");
        
    free(copy);
    
    return EXIT_SUCCESS;
}
*/