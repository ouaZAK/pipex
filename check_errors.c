/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:43:52 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/04 09:58:06 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_sub_dir(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != '/')
		i++;
	if (str[i] == '/' && ft_strstr(str, ".sh"))
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

static void	check_print_errors(char *path, char *cmd, char c, t_vars *va)
{
	if (access(path, F_OK) && c == 'c')
		free_exit_msg(ft_strjoin(ft_strdup(cmd), ": command not found"), \
			COM_N, va);
	else if (access(path, F_OK) && c == 'p')
		free_exit_msg(ft_strjoin(ft_strdup(cmd), ": No such file or directory"), \
			NF_ND, va);
	else if (access(path, X_OK))
		free_exit_msg(ft_strjoin(ft_strdup(cmd), ": permission denied: "), \
			PERM_D, va);
}

void	check_errors(char *path, char **cmd, t_vars *va)
{
	if (cmd[0][0] != '/' && cmd[0][0] != '.' && check_sub_dir(cmd[0]))
		cmd[0] = add_point(cmd[0]);
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
		check_print_errors(cmd[0], cmd[0], 'p', va);
	else
	{
		path = join_path_to_cmd(path, cmd[0]);
		if (cmd[0][0] != '/' && ft_strstr(cmd[0], "/"))
			check_print_errors(path, cmd[0], 'p', va);
		else if (!ft_strcmp(path, "emptypath", '0'))
			check_print_errors(path, cmd[0], 'p', va);
		else
			check_print_errors(path, cmd[0], 'c', va);
		free(path);
	}
}
