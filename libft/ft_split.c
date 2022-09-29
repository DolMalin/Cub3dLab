/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:43:07 by aandric           #+#    #+#             */
/*   Updated: 2021/11/17 13:17:57 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c && s[i + 1] == c)
			word++;
		if (s[i] != c && s[i + 1] == '\0')
			word++;
		i++;
	}
	return (word);
}

static int	ft_count_letters(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char	**ft_free_tab(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (NULL);
}

static char	**ft_create_tab(const char *str, char c)
{
	char	**words;

	if (!str)
		return (NULL);
	words = malloc(sizeof(char *) * (ft_count_words(str, c) + 1));
	if (!words)
		return (NULL);
	return (words);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**words;

	words = ft_create_tab(s, c);
	if (!words)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (i < ft_count_words(s, c) && s[k])
	{
		while (s[k] == c && s[k])
			k++;
		words[i] = malloc(sizeof(char) * (ft_count_letters(&s[k], c) + 1));
		if (!words[i])
			return (ft_free_tab(words, i));
		while (s[k] != c && s[k])
			words[i][j++] = s[k++];
		words[i++][j] = '\0';
		j = 0;
	}
	words[i] = 0;
	return (words);
}
