/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:38:01 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/02/12 11:45:24 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_quote(char *str, char **env, t_vars *va)
{
	char	**cmd;
	char	*path;

	path = NULL;
	cmd = split_it(str, va);
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
