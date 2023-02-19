/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:59:01 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/02/19 14:45:18 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	heredoc_func(char **av, t_vars va)
{
	char	*str;
	char	*line;

	line = NULL;
	close(va.p1[0]);
	while (1)
	{
		write(2, "heredoc> ", 9);
		str = get_next_line(0);
		if (ft_strcmp(str, av[2], '\n'))
			line = ft_strjoin(line, str);
		if (!ft_strcmp(str, av[2], '\n'))
		{
			write (va.p1[1], line, ft_strlen(line));
			free(str);
			free(line);
			break ;
		}
		free(str);
	}
}

void	which_child(char **av, char **env, int ac, t_vars va)
{
	if (ac >= 6 && !ft_strcmp(av[1], "here_doc", 0))
		heredoc_func(av, va);
	else if (ac >= 5)
		first_child(av, env, va);
}

void	parent_and_childs(char **av, char **env, int ac, t_vars va)
{
	va.i = 1;
	va.j = -1;
	while (va.i <= ac - 4)
	{
		if (va.i == ac - 4)
		{
			while (++va.j < ac - 5)
				wait(NULL);
			the_parent(av, env, va, ac);
		}
		va.pid = fork();
		if (va.pid == 0)
			middle_childs(av, env, va, va.i);
		open_pipes(&va, va.i);
		va.i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_vars	va;

	if (ac < 5)
	{
		ft_putstr_fd("write as follow :\n", 2);
		ft_putstr_fd("-> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 2);
		exit_msg("-> ./pipex here_doc LIMITER cmd cmd1 file\n", 2);
	}
	set_first_pipes(&va);
	va.pid = fork();
	if (va.pid == -1)
		exit_msg("fork error\n", 2);
	if (va.pid == 0)
		which_child(av, env, ac, va);
	else
	{
		wait(NULL);
		parent_and_childs(av, env, ac, va);
	}
	return (0);
}
