/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:59:51 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/01 09:59:54 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*cal;

	i = 0;
	cal = malloc(size * count);
	if (!cal)
		return (0);
	while (i < size * count)
	{
		((unsigned char *)cal)[i] = '\0';
		i++;
	}
	return ((void *)cal);
}

static void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = -1;
	if (!dst && !src)
		return (0);
	if (src >= dst)
		while (++i < len)
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	else
		while (len--)
			*(((unsigned char *)dst) + len) = *(((unsigned char *)src) + len);
	return (dst);
}

static int	word_count(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
			count++;
		while (*str && *str != c)
			str++;
	}
	return (count);
}

static char	**word_len(char *s, char c, char **str)
{
	int		i;
	int		j;

	i = 0;
	while (*s)
	{
		j = 0;
		while (*s && *s == c)
			s++;
		while (s[j] && s[j] != c)
			j++;
		if (*s)
		{
			str[i] = (char *)ft_calloc(j + 1, sizeof(char));
			ft_memmove(str[i], s, j);
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		nbw;
	char	**str;

	if (!s)
		return (NULL);
	nbw = word_count((char *)s, c);
	str = (char **)ft_calloc(nbw + 1, sizeof(char *));
	if (!str)
		return (0);
	str = word_len((char *)s, c, str);
	return (str);
}
