/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:11:16 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/01/23 09:11:57 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **env)
{
	char	*path;
	int		x;
	int		y;

	path = "PATH=";
	y = -1;
	while (env[++y])
	{
		x = 0;
		while (env[y][x] == path[x])
			x++;
		if (!env[y][x + 1])
			return (NULL);
		if (!path[x])
			return (env[y]);
	}
	exit_msg("pipex:command not found :");
	return (NULL);
}

char	*join_path_to_cmd(char *path, char *cmd)
{
	char	**str;
	char	**cpy;
	char	*tmp;
	int		y;

	y = 0;
	cpy = ft_split(path, '=');
	str = ft_split(cpy[1], ':');
	ft_free(cpy, 0);
	cpy = ft_split(cmd, ' ');
	y = -1;
	while (str[++y])
	{
		tmp = ft_strjoin_2(str[y], cpy[0]);
		if (!access(tmp, X_OK))
		{
			ft_free(str, ++y);
			ft_free(cpy, 0);
			return (tmp);
		}
		free(tmp);
	}
	free(str);
	exit_msg("pipex >??????");
	return (NULL);
}

