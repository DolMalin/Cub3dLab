/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:39:51 by aandric           #+#    #+#             */
/*   Updated: 2022/03/03 11:36:07 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_save_rest(char *buffer, char *shifted_buffer)
{
	int	i;

	i = 0;
	while (*shifted_buffer)
	{
		buffer[i] = *shifted_buffer;
		shifted_buffer++;
		i++;
	}
	buffer[i] = '\0';
}

char	*get_line(char *line, char *buffer, int fd)
{
	int	ret;

	ret = 1;
	while (ret > 0)
	{
		line = ft_strjoin_gnl(line, buffer);
		if (!line)
		{
			free(line);
			return (NULL);
		}
		if (ft_chrn(buffer) != -1)
		{
			ft_save_rest(buffer, &buffer[ft_chrn(buffer) + 1]);
			return (line);
		}	
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
		{
			free(line);
			return (NULL);
		}
		buffer[ret] = '\0';
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char) * 1);
	if (!line)
		return (NULL);
	line[0] = 0;
	line = get_line(line, buffer, fd);
	if (ft_strlen(line))
		return (line);
	free(line);
	return (NULL);
}
