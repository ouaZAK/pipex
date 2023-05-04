/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 10:02:08 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/04 09:44:01 by zouaraqa         ###   ########.fr       */
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
		return (0);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = '/';
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

void	ft_free(char **str, int i)
{
	if (!str)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	exit_msg(char *str, int nb, char **cmd)
{
	perror(str);
	ft_free(cmd, 0);
	free(str);
	exit(nb);
}

void	free_exit_msg(char *str, int nb, t_vars *va)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	free(str);
	va->exit = nb;
}
