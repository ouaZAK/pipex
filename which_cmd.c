/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:59:39 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/02/02 10:46:12 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_sub_dir(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != '/')
		i++;
	if (str[i] == '/')
		return (1);
	return (0);
}

char	*add_point(char *str)
{
	char	*cmd;
	int		i;
	int		y;

	i = 0;
	y = 0;
	cmd = ft_calloc(sizeof(char), ft_strlen(str) + 3);
	cmd[i++] = '.';
	cmd[i++] = '/';
	while (str[y])
		cmd[i++] = str[y++];
	free(str);
	return (cmd);
}

void	check_print_errors(char *path, char *cmd, char c, char **cmds)
{
	if (access(path, F_OK) && c == 'c')
		free_exit_msg(ft_strjoin("pipex: command not found: ", cmd), \
			COM_N, cmds);
	else if (access(path, F_OK) && c == 'p')
		free_exit_msg(ft_strjoin("pipex: no such file or directory: ", cmd), \
			NF_ND, cmds);
	else if (access(path, X_OK))
		free_exit_msg(ft_strjoin("pipex: permission denied: ", cmd), \
			PERM_D, cmds);
}

void	which_cmd(char **env, char *path, char **cmd)
{
	if (cmd[0][0] != '/' && check_sub_dir(cmd[0]))
		cmd[0] = add_point(cmd[0]);
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
	{
		check_print_errors(cmd[0], cmd[0], 'p', cmd);
		execve(cmd[0], cmd, env);
		free_exit_msg(ft_strjoin("pipex: permission denied: ", cmd[0]), \
			PERM_D, cmd);
	}
	else
	{
		path = join_path_to_cmd(path, cmd[0]);
		check_print_errors(path, cmd[0], 'c', cmd);
		execve(path, cmd, env);
	}
}
