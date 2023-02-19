/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_and_childs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:39:35 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/02/19 10:46:44 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	first_child(char **av, char **env, t_vars va)
{
	char	**cmd;
	char	*path;

	path = NULL;
	close(va.p1[0]);
	dup2(va.p1[1], 1);
	va.fd = open(av[1], O_RDONLY);
	if (va.fd == -1)
		free_exit_msg(ft_strjoin(av[1], ": No such file or directory"), \
			1, NULL);
	dup2(va.fd, 0);
	cmd = split_it(av[2], &va);
	if (!cmd[0])
		free_exit_msg(ft_strjoin(av[2], ": command not found"), COM_N, cmd);
	path = get_path(env);
	which_cmd(env, path, cmd);
}

void	middle_childs(char **av, char **env, t_vars va, int i)
{
	char	**cmd;
	char	*path;

	set_pipes(&va, va.i);
	path = NULL;
	cmd = split_it(av[i + 2], &va);
	if (!cmd[0])
		free_exit_msg(ft_strjoin(av[i + 2], \
			": command not found"), COM_N, cmd);
	path = get_path(env);
	which_cmd(env, path, cmd);
}

static void	check_last_file(char **av, int ac, t_vars *va)
{
	if (!ft_strcmp(av[1], "here_doc", 0))
	{
		va->fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (va->fd == -1 && *av[ac - 1])
			free_exit_msg(ft_strjoin(av[ac - 1], \
				": permission denied"), 1, NULL);
		else if (!*av[ac - 1])
			free_exit_msg(ft_strjoin(av[ac - 1], \
				": No such file or directory"), NF_ND, NULL);
	}
	else
	{
		va->fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (va->fd == -1 && *av[ac - 1])
			free_exit_msg(ft_strjoin(av[ac - 1], \
				": permission denied"), 1, NULL);
		else if (!*av[ac - 1])
			free_exit_msg(ft_strjoin(av[ac - 1], \
				": No such file or directory"), NF_ND, NULL);
	}
}

void	the_parent(char **av, char **env, t_vars va, int ac)
{
	char	**cmd;
	char	*path;

	path = NULL;
	set_pipes_parent(&va, va.i);
	check_last_file(av, ac, &va);
	dup2(va.fd, 1);
	cmd = split_it(av[ac - 2], &va);
	if (!cmd[0])
		free_exit_msg(ft_strjoin(av[ac - 2], \
			": command not found"), COM_N, cmd);
	path = get_path(env);
	which_cmd(env, path, cmd);
}
