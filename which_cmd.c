/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:59:39 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/01/23 11:52:32 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	executingu(char **cmd, char *path, char **env, char *s)
{
	char	**str;
	char	**tmp;
	int		i;

	i = 0;
	if (cmd[0][0] == '/')
	{
		str = ft_split(s, '/');
		while (str && str[i + 1])
			i++;
		tmp = ft_split(str[i], ' ');
		ft_free(str, 0);
		execve(cmd[0], tmp, env);
	}
	else
	{
		path = join_path_to_cmd(path, cmd[i]);
		execve(path, cmd, env);
	}		
}

void	which_cmd(char *av, char **env, char *path, char **cmd)
{
	char	**str;

	if (cmd[0][0] != '.' && check_bash(cmd[0]) != 1)
		executingu(cmd, path, env, av);
	else if (cmd[0][0] == '.')
		execve(av, cmd, env);
	else if (check_bash(cmd[0]) == 1)
	{
		path = join_path_to_cmd(path, cmd[0]);
		execve(path, cmd, env);
	}
	else
		path = join_path_to_cmd(path, av);
	str = ft_split(av, ' ');
	execve(path, str, env);
}
