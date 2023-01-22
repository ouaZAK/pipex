/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 08:59:06 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/01/22 11:40:01 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **env)
{
	char	*path;
	int		x;
	int		y;

	path = "PATH=";
	y = -1;
	while (env[++y])
	{
		x = 0;
		while (env[y][x] == path[x])
			x++;
		if (!env[y][x + 1])
			return (NULL);
		if (!path[x])
			return (env[y]);
	}
	exit_msg("pipex:command not found :");
	return (NULL);
}

char	*join_path_to_cmd(char *path, char *cmd)
{
	char	**str;
	char	**cpy;
	char	*tmp;
	int		y;

	y = 0;
	cpy = ft_split(path, '=');
	str = ft_split(cpy[1], ':');
	ft_free(cpy, 0);
	cpy = ft_split(cmd, ' ');
	y = -1;
	while (str[++y])
	{
		tmp = ft_strjoin_2(str[y], cpy[0]);
		if (!access(tmp, X_OK))
		{
			ft_free(str, ++y);
			return (tmp);
		}
		free(tmp);
	}
	free(str);
	exit_msg("pipex >??????");
	return (NULL);
}

char	*check_errors(int ac, char **av, char **env, char *path)
{
	if (ac > 5)
		exit_msg("wrong args\n");
	if (access(av[1], R_OK) == -1)
		exit_msg("file has no permission to read\n");
	path = get_path(env);
	return (path);
}

char	*check_cmd(char *str)
{
	char	**s;
	int		i;

	i = -1;
	s = ft_split(str, ' ');
	// ft_putstr_fd(str, 1);
	// printf("%d\n",access(str, X_OK));
	if (str[0] == '/' && access(s[0], X_OK) != -1)
	{
		s = ft_split(str, '/');
		while (s[++i])
			if (!s[i + 1])
				return (s[i]);
	}
	else if ((str[0] == '.' && str[1] == '/' && access(str, X_OK) != -1)
		|| (str[0] != '.' && str[1] != '/' && access(str, X_OK) != -1))
		return (str);
	return (NULL);
}

void	child(char **av, char **env, char *path, int pfd[])
{
	char	**str;
	char	*cmd;
	int		fd;

	close(pfd[0]);
	cmd = check_cmd(av[2]);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit_msg("child fd error\n");
	dup2(pfd[1], 1);
	dup2(fd, 0);
	// ft_putstr_fd(cmd, 1);
	if (cmd)
	{
		path = join_path_to_cmd(path, cmd);
		str = ft_split(cmd, ' ');
		execve(path, str, env);
	}
	else
		path = join_path_to_cmd(path, av[2]);
	str = ft_split(av[2], ' ');
	execve(path, str, env);
}

int	main(int ac, char **av, char **env)
{
	char	**str;
	char	*path;
	int		pfd[2];
	int		fd;
	int		pid;

	path = check_errors(ac, av, env, path);
	if (pipe(pfd) == -1)
		free_exit("pipex : command not fount :");
	pid = fork();
	if (pid == 0)
		child(av, env, path, pfd);
	else
	{
		wait(NULL);
		close(pfd[1]);
		fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			exit_msg("parent fd error\n");
		dup2(fd, 1);
		dup2(pfd[0], 0);
		path = join_path_to_cmd(path, av[3]);
		str = ft_split(av[3], ' ');
		execve(path, str, env);
	}
}
