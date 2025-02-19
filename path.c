/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:54:31 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/04 10:15:52 by zouaraqa         ###   ########.fr       */
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
		while (env[y][x] && env[y][x] == path[x])
				x++;
		if (!path[x] && env[y][x])
			return (&env[y][x]);
		else if (!env[y][x])
			return ("emptypath");
	}
	return ("/usr/local/bin:/usr/bin:/bin: \
					/usr/sbin:/sbin:/usr/local/munki");
}

char	*join_path_to_cmd(char *path, char *cmd)
{
	char	**str;
	char	*tmp;
	int		y;

	if (!ft_strcmp(path, "emptypath", '0'))
		return (ft_strdup("emptypath"));
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
	return (ft_strdup("wrongpath"));
}
