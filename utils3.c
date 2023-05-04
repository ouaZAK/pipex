/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 10:02:43 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/04 09:57:13 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

int	ft_strstr(char *haystack, char *needle)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!haystack)
		return (0);
	if (!*needle)
		return (0);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && needle[j])
			j++;
		if (needle[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

char	*cpy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	if (!dst || !src)
		return (0);
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

int	ft_strcmp(char *s1, char *s2, char c)
{
	int		i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (c == '\n')
		if (s1[i] == '\n' && s2[i] == '\0')
			return (0);
	return (s1[i] - s2[i]);
}

char	*ft_strdup(char *str)
{
	char	*cpy;
	int		len;
	int		i;

	len = ft_strlen(str);
	cpy = malloc(sizeof(char) * (len + 1));
	if (!cpy)
		return (0);
	i = 0;
	while (str[i])
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
