/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 08:59:06 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/01/23 11:52:21 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **av, char **env, char *path, int pfd[])
{
	char	**cmd;
	int		fd;

	close(pfd[0]);
	cmd = ft_split(av[2], ' ');
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit_msg("child fd error\n");
	dup2(pfd[1], 1);
	dup2(fd, 0);
	which_cmd(av[2], env, path, cmd);
}

void	parent(char **av, char **env, char *path, int pfd[])
{
	char	**cmd;
	int		fd;

	close(pfd[1]);
	cmd = ft_split(av[3], ' ');
	fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		exit_msg("parent fd error\n");
	dup2(pfd[0], 0);
	dup2(fd, 1);
	which_cmd(av[3], env, path, cmd);
}

int	main(int ac, char **av, char **env)
{
	char	*path;
	int		pfd[2];
	int		pid;

	path = NULL;
	path = check_errors(ac, av, env, path);
	if (pipe(pfd) == -1)
		free_exit("pipex : command not fount :");
	pid = fork();
	if (pid == 0)
		child(av, env, path, pfd);
	else
	{
		wait(NULL);
		parent(av, env, path, pfd);
	}
}
