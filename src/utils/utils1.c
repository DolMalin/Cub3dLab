/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <pdal-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:42:55 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/11/09 13:28:16 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	lines_count(char *file)
{
	int		len;
	char	*buffer;
	int		fd;

	len = 0;
	fd = open(file, O_RDONLY);
	buffer = get_next_line(fd);
	while (buffer)
	{
		len++;
		free(buffer);
		buffer = get_next_line(fd);
	}
	return (len);
}

void	free_array(void	**array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_unterminated_array(void **array, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		return ;
	while (i < n)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

size_t	array_len(void **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

t_bool	is_config_line(char *line)
{
	char	*trim_line;
	size_t	len;
	t_bool	ret;

	ret = false;
	if (!line)
		return (true);
	trim_line = trim(line, " \t\r\n");
	if (!trim_line)
		return (false);
	len = ft_strlen(trim_line);
	if (ft_strnstr(trim_line, "NO", len) || ft_strnstr(trim_line, "SO", len))
			ret = true;
	else if (ft_strnstr(trim_line, "WE", len)
		|| ft_strnstr(trim_line, "EA", len))
			ret = true;
	else if (ft_strnstr(trim_line, "F", len) || ft_strnstr(trim_line, "C", len))
			ret = true;
	free(trim_line);
	return (ret);
}
