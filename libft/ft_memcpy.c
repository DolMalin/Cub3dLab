/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:57:50 by aandric           #+#    #+#             */
/*   Updated: 2021/11/06 15:23:14 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;	

	i = 0;
	if (n > 0 && (dst == 0 && src == 0))
		return (dst);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>

int main() {

    int array [] = {54, 12, 41, 65, 32};
    int * copy = NULL;
    int length = sizeof(int) * 5;

    copy = (int *) malloc( length );
    ft_memcpy( copy, array, length);
        
    for( length=0; length<5; length++ ) {
        printf( "%d ", copy[ length ] );
    }
    printf("\n");
        
    free(copy);
    
    return EXIT_SUCCESS;
}
*/