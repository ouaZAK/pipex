/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_and_childs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:39:35 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/03/07 09:39:43 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	executing_cmd(char **env, t_vars va)
{
	if (va.cmd[0][0] != '/' && va.cmd[0][0] != '.' && check_sub_dir(va.cmd[0]))
		va.cmd[0] = add_point(va.cmd[0]);
	if (va.cmd[0][0] == '/' || va.cmd[0][0] == '.')
		execve(va.cmd[0], va.cmd, env);
	else
	{
		va.path = join_path_to_cmd(va.path, va.cmd[0]);
		execve(va.path, va.cmd, env);
		free(va.path);
	}
}

void	first_child(char **env, t_vars va)
{
	if (va.fd != -1)
	{
		close(va.p1[0]);
		dup2(va.p1[1], 1);
		dup2(va.fd, 0);
		executing_cmd(env, va);
	}
	ft_free(va.cmd, 0);
	free(va.pid);
	close_fds(&va);
	exit(va.exit);
}

void	middle_childs(char **env, t_vars va)
{
	set_pipes(&va, va.i);
	executing_cmd(env, va);
	ft_free(va.cmd, 0);
	free(va.pid);
	close_fds(&va);
	exit(va.exit);
}

static void	check_last_file(char **av, int ac, t_vars *va)
{
	if (!ft_strcmp(av[1], "here_doc", 0))
	{
		va->fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (va->fd == -1)
			print_msg_error(ft_strjoin("pipex: ", av[ac - 1]), va);
	}
	else
	{
		va->fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (va->fd == -1)
			print_msg_error(ft_strjoin("pipex: ", av[ac - 1]), va);
	}
}

void	last_child(char **av, char **env, t_vars va, int ac)
{
	check_last_file(av, ac, &va);
	if (va.fd != -1)
	{
		set_pipes_parent(&va, va.i);
		dup2(va.fd, 1);
		executing_cmd(env, va);
	}
	ft_free(va.cmd, 0);
	free(va.pid);
	close_fds(&va);
	exit(va.exit);
}
