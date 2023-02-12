/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 08:59:06 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/02/12 16:03:47 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child(char **av, char **env, int pfd[], t_vars *va)
{
	char	**cmd;
	char	*path;
	int		fd;

	path = NULL;
	close(pfd[0]);
	dup2(pfd[1], 1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		free_exit_msg(ft_strjoin(av[1], ": No such file or directory"), \
			1, NULL);
	dup2(fd, 0);
	while (*av[2] && *av[2] == ' ')
		av[2]++;
	cmd = split_it(av[2], va);
	if (!cmd[0])
		exit_msg("pipex : : command not found", COM_N);
	path = get_path(env);
	which_cmd(env, path, cmd);
}

static void	parent(char **av, char **env, int pfd[], t_vars *va)
{
	char	**cmd;
	char	*path;
	int		fd;

	path = NULL;
	close(pfd[1]);
	dup2(pfd[0], 0);
	fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		free_exit_msg(ft_strjoin(av[4], ": permission denied"), 1, NULL);
	dup2(fd, 1);
	while (*av[3] && *av[3] == ' ')
		av[3]++;
	cmd = split_it(av[3], va);
	if (!cmd[0])
		exit_msg("pipex : : command not found", COM_N);
	path = get_path(env);
	which_cmd(env, path, cmd);
}

int	main(int ac, char **av, char **env)
{
	t_vars	va;
	int		pfd[2];
	int		pid;

	if (ac != 5)
		exit_msg("wrong args", 2);
	if (pipe(pfd) == -1)
		exit_msg("error in pipe", 2);
	pid = fork();
	if (pid == -1)
		exit_msg("error in fork", 2);
	if (pid == 0)
		child(av, env, pfd, &va);
	else
	{
		parent(av, env, pfd, &va);
		wait(NULL);
	}
}
