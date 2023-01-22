/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 08:59:06 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/01/22 19:55:31 by zouaraqa         ###   ########.fr       */
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
			ft_free(cpy, 0);
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

int	check_bash(char *str)
{
	char *tmp;
	int	i;

	i = 0;
	tmp = strdup("bash"); // 
	while (str[i] && tmp[i] && str[i] == tmp[i])
		i++;
	if (!str[i] && !tmp[i])
	{
		free(tmp);
		return (1);
	}
	return (0);
}

int	check_normal_cmd(char *str, char *path)
{
	path = join_path_to_cmd(path, str);
	if (access(path, X_OK) == 0)
		return (1);
	return (0);
}

char	**check_cmd(char *str, char **env, char *path)
{
	char	**s;
	int		i;

	i = -1;
	s = ft_split(str, ' ');
	if (str[0] == '/' && access(s[0], X_OK) != -1)
	{
		ft_free(s, 0);
		s = ft_split(str, '/');
		while (s[++i])
			if (!s[i + 1])
				return (s);
		free(s);
	}
	else if ((str[0] == '.' && access(str, X_OK) != -1))
		return (s);
	else if (check_bash(s[0]) == 1 || check_normal_cmd(s[0], path) == 1)
		return (s);
	exit_msg("pipex :  not script not cmd");
	return (NULL);
}

void	executingu(char **cmd, char *path, char **env, char **av)
{
	char	**str;
	int		i;

	i = 0;
	while (cmd && cmd[i + 1])
		i++;
	path = join_path_to_cmd(path, cmd[i]);
	str = ft_split(cmd[i], ' ');
	ft_free(cmd, 0);
	execve(path, str, env);
}

void	child(char **av, char **env, char *path, int pfd[])
{
	char	**str;
	char	**cmd;
	int		fd;
	int		i;

	i = 0;
	close(pfd[0]);
	cmd = check_cmd(av[2], env, path);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit_msg("child fd error\n");
	dup2(pfd[1], 1);
	dup2(fd, 0);
	if (cmd[0][0] != '.' && check_bash(cmd[0]) != 1)
		executingu(cmd, path, env, av);
	else if (cmd[0][0] == '.')
		execve(av[2], cmd, env);
	else if (check_bash(cmd[0]) == 1)
	{
		path = join_path_to_cmd(path, cmd[0]);
		execve(path, cmd, env);
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
