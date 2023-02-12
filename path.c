/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:11:16 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/02/12 11:57:20 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **env, char *cmd, char *av)
{
	char	*path;
	int		x;
	int		y;

	path = "PATH=";
	y = -1;
	while (env[++y])
	{
		x = 0;
		while (env[y][x] && env[y][x] == path[x])
				x++;
		if (!env[y][x])
			if (av[0] == '.' || av[0] == '/')
				return ("/usr/local/bin:/usr/bin:/bin: \
						/usr/sbin:/sbin:/usr/local/munki");
		if (!path[x])
			return (&env[y][x]);
	}
	y = -1;
	if (av[0] == '.' || av[0] == '/')
		return ("/usr/local/bin:/usr/bin:/bin: \
				/usr/sbin:/sbin:/usr/local/munki");
	free_exit_msg(ft_strjoin("pipex: command not found : ", cmd), COM_N, NULL);
	return (NULL);
}

char	*join_path_to_cmd(char *path, char *cmd)
{
	char	**str;
	char	*tmp;
	int		y;

	y = 0;
	str = ft_split(path, ':');
	y = -1;
	while (str[++y])
	{
		tmp = ft_strjoin_2(str[y], cmd);
		if (!access(tmp, X_OK))
		{
			ft_free(str, ++y);
			return (tmp);
		}
		free(tmp);
	}
	free(str);
	return (NULL);
}
