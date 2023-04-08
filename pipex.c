/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:59:01 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/03/07 20:07:22 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	parent(t_vars va)
{
	close_fds(&va);
	while (va.i--)
	{
		va.wpid = waitpid(va.pid[va.i], &va.status, 0);
		if (va.wpid == va.pid[va.loop] && WIFEXITED(va.status))
			va.exit = WEXITSTATUS(va.status);
	}
	free(va.pid);
	if (va.split_with == 'h')
		unlink("tmp");
	exit(va.exit);
}

static void	parent_and_childs(char **av, char **env, int ac, t_vars va)
{
	va.i = 0;
	va.path = get_path(env);
	while (va.i <= va.loop)
	{
		va.cmd = which_split(av, va, ac, va.i);
		check_empty_cmd(av, &va);
		if (*va.cmd)
		{
			check_errors(va.path, va.cmd, &va);
			va.pid[va.i] = fork();
			if (va.pid[va.i] == -1)
				exit_msg("pipex :", 2, NULL);
			if (va.pid[va.i] == 0 && va.i == 0)
				first_child(env, va);
			else if (va.pid[va.i] == 0 && va.i != va.loop && va.i != 0)
				middle_childs(env, va);
			else if (va.pid[va.i] == 0 && va.i == va.loop)
				last_child(av, env, va, ac);
		}
		open_pipes(&va, va.i);
		ft_free(va.cmd, 0);
		va.i++;
	}
	parent(va);
}

int	main(int ac, char **av, char **env)
{
	t_vars	va;

	if (ac < 5)
	{
		ft_putstr_fd("write as follow :\n", 2);
		ft_putstr_fd("-> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 2);
		ft_putstr_fd("-> ./pipex here_doc LIMITER cmd cmd1 file\n", 2);
		exit(2);
	}
	open_file_or_herdoc(av, ac, &va);
	set_first_pipes(&va);
	parent_and_childs(av, env, ac, va);
	return (0);
}
