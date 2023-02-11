/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:38:01 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/02/11 10:52:52 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_quote(char *str, char **env, t_vars *va)
{
	char	**cmd;
	char	*path;

	path = NULL;
	while (*str && *str == ' ')
		str++;
	cmd = split_it(str, va);
	if (!cmd)
		free_exit_msg(ft_strjoin("pipex: command not found: ", str), \
			COM_N, NULL);
	if (str[0] == '/')
	{
		check_print_errors(cmd[0], cmd[0], 'p', cmd);
		execve(cmd[0], cmd, env);
	}
	else
	{
		path = get_path(env, cmd[0], NULL);
		path = join_path_to_cmd(path, cmd[0]);
		check_print_errors(path, cmd[0], 'c', cmd);
	}
	execve(path, cmd, env);
}
