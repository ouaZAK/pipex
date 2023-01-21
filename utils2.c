/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 10:36:50 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/01/21 13:11:30 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (((unsigned char *)s)[i])
		i++;
	return (i);
}

char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
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
	str[i++] = '/';
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	// s1 = NULL;
	return (str);
}

void	ft_free(char **str, int i)
{
	while (str[i])
		free(str[i++]);
	free(str);
}

void	exit_msg(char *str)
{
	perror(str);
	exit(1);
}