/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:59:39 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/01/26 13:21:07 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_print_errors(char *path, char *cmd, char c)
{
	if (access(path, F_OK) && c == 'c')
		exit_msg(ft_strjoin("pipex: command not found: ", cmd), COM_N);
	else if (access(path, F_OK) && c == 'p')
		exit_msg(ft_strjoin("pipex: no such file or directory: ", cmd), NF_ND);
	else if (access(path, X_OK))
		exit_msg(ft_strjoin("pipex: permission denied: ", cmd), PERM_D);
}

void	which_cmd(char **env, char *path, char **cmd)
{
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
	{
		check_print_errors(cmd[0], cmd[0], 'p');
		execve(cmd[0], cmd, env);
		exit_msg(ft_strjoin("pipex: permission denied: ", cmd[0]), PERM_D);
	}
	else
	{
		path = get_path(env, cmd[0]);
		path = join_path_to_cmd(path, cmd[0]);
		check_print_errors(path, cmd[0], 'c');
		execve(path, cmd, env);
	}
}

static int	countingu(char *str, int len, char c)
{
	int	count;

	count = 0;
	while (str[len] != c && len >= 0)
	{
		len--;
		count++;
	}
	return (count);
}

static void	*awk_split(char *str)
{
	char	*s;
	int		i;
	int		end;
	int		len;

	i = 0;
	end = 0;
	len = ft_strlen(str);
	while (str[i] && str[i] != '"' && str[i] != '\'')
		i++;
	if (i == len)
	{
		while (str[end] && str[end] != ' ')
			end++;
		return (&str[end + 1]);
	}
	else if (str[i] == '"')
		end = countingu(str, len, '"');
	else if (str[i] == '\'')
		end = countingu(str, len, '\'');
	len -= i + end;
	s = ft_calloc(sizeof(char), len);
	end = 0;
	i++;
	while (str[i] && len-- > 1)
		s[end++] = str[i++];
	return (s);
}

void	check_awk(char *str, char **env)
{
	char	**cmd;
	char	*path;
	int		i;
	int		y;

	i = 0;
	y = -1;
	path = NULL;
	while (str[i] && str[i] != ' ')
		i++;
	cmd = ft_calloc(sizeof(char *), 3);
	cmd[0] = ft_calloc(sizeof(char), i + 1);
	while (++y < i)
		cmd[0][y] = str[y];
	if (str[0] == '/')
		check_print_errors(cmd[0], cmd[0], 'p');
	else
	{
		path = get_path(env, cmd[0]);
		path = join_path_to_cmd(path, cmd[0]);
		check_print_errors(path, cmd[0], 'c');
	}
	cmd[1] = awk_split(str);
	cmd[2] = NULL;
	execve(path, cmd, env);
}
