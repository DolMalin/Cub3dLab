/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:40:07 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/10/18 13:01:49 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error(char *error_msg, void **array)
{	
	printf("%s", error_msg);
	free_array((void **)array);
	exit(EXIT_FAILURE);
}
