/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 08:59:06 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/01/21 17:44:03 by zouaraqa         ###   ########.fr       */
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
	return (NULL);
}

char	*check_errors(int ac, char **av, char **env, char *path)
{
	int	x;

	if (ac > 5)
		exit_msg("wrong args\n");
	x = access(av[1], R_OK);
	if (x == -1)
		exit_msg("file has no permission to read\n");
	path = get_path(env);
	if (!path)
		exit_msg("no path\n");
	return (path);
}

int	main(int ac, char **av, char **env)
{
	char	*path;
	int		pfd[2];
	int		fd;
	int		pid;

	path = NULL;
	path = check_errors(ac, av, env, path);
	if (pipe(pfd) == -1)
	{
		free(path);
		exit_msg("error with pipe");
	}
	pid = fork();
	if (pid == 0)
	{
		close(pfd[0]);
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			exit_msg("child fd error\n");
		dup2(pfd[1], 1);
		dup2(fd, 0);
		path = join_path_to_cmd(path, av[2]);
		if (!path)
			exit_msg("child : no path match cmd\n");
		char **str = ft_split(av[2], ' ');
		execve(path, str, env);
		// printf("path child is = %s\n", path);
	}
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
		if (!path)
			exit_msg("pipex");
		// printf("c p = %s\n",path);
		char **str = ft_split(av[3], ' ');
		execve(path, str, env);
		// printf("path parent is = %s\n", path);
	}
	
}
