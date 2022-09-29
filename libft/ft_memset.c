/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:47:43 by aandric           #+#    #+#             */
/*   Updated: 2021/11/17 16:54:21 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = len;
	while (i-- > 0)
		*(unsigned char *)b++ = c;
	return (b - len);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {\
	char *test;
	
	test = malloc(12);
	printf("%p | %p\n", test, &test);
    int array [] = { 54, 85, 20, 63, 21 };
    size_t size = sizeof( int ) * 5;
    int length;

  
    for( length=0; length<5; length++) {
        printf( "%d ", array[ length ] );
    }
    printf( "\n" );

    ft_memset( array, 0, size );

    for( length=0; length<5; length++) {
        printf( "%d ", array[ length ] );
    }
    printf( "\n" );

    return 0;
}
*/