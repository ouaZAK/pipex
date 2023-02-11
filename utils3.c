/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 09:04:04 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/02/11 11:08:15 by zouaraqa         ###   ########.fr       */
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
	{
		free(s1);
		s1 = NULL;
		return (0);
	}
	i = -1;
	j = 0;
	while (s1 && s1[++i])
		str[i] = s1[i];
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	s1 = NULL;
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
