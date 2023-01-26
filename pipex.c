/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 08:59:06 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/01/26 13:12:28 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **av, char **env, int pfd[])
{
	char	**cmd;
	char	*path;
	int		fd;

	path = NULL;
	close(pfd[0]);
	dup2(pfd[1], 1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit_msg(ft_strjoin("pipex: no such file or directory: ", av[1]), 1);
	dup2(fd, 0);
	if (ft_strstr(av[2], "awk") == 1)
		check_awk(av[2], env);
	cmd = ft_split(av[2], ' ');
	path = get_path(env, cmd[0]);
	if (!cmd[0])
		exit_msg("pipex : command not found: ", COM_N);
	which_cmd(env, path, cmd);
}

void	parent(char **av, char **env, int pfd[])
{
	char	**cmd;
	char	*path;
	int		fd;

	path = NULL;
	close(pfd[1]);
	dup2(pfd[0], 0);
	fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		exit_msg(ft_strjoin("pipex: permission denied: ", av[4]), 1);
	dup2(fd, 1);
	if (ft_strstr(av[3], "awk") == 1)
		check_awk(av[3], env);
	cmd = ft_split(av[3], ' ');
	path = get_path(env, cmd[0]);
	if (!cmd[0])
		exit_msg("pipex : command not found: ", COM_N);
	which_cmd(env, path, cmd);
}

int	main(int ac, char **av, char **env)
{
	int		pfd[2];
	int		pid;

	if (ac != 5)
		exit_msg("wrong args", 2);
	if (pipe(pfd) == -1)
		free_exit("pipex : command not fount :");
	pid = fork();
	if (pid == 0)
		child(av, env, pfd);
	else
	{
		wait(NULL);
		parent(av, env, pfd);
	}
}
