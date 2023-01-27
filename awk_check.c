/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   awk_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:38:01 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/01/27 12:24:38 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static char	*store_awk(char *str)
{
	char	*cmd;
	int		count;
	int		i;
	int		y;

	count = 0;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	y = i;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		count++;
		i++;
	}
	cmd = ft_calloc(sizeof(char), count + 1);
	i = 0;
	while (i < count)
		cmd[i++] = str[y++];
	return (cmd);
}

static char	**awk_split(char *str)
{
	char	**cmd;
	int		i;
	int		end;
	int		len;

	i = 0;
	end = 0;
	len = ft_strlen(str);
	cmd = ft_calloc(sizeof(char *), 3);
	cmd[0] = store_awk(str);
	while (str[i] && str[i] != '"' && str[i] != '\'')
		i++;
	if (i == len)
		return (NULL);
	if (str[i] == '"')
		end = countingu(str, len, '"');
	else if (str[i] == '\'')
		end = countingu(str, len, '\'');
	len -= i + end;
	cmd[1] = ft_calloc(sizeof(char), len);
	end = 0;
	i++;
	while (str[i] && len-- > 1)
		cmd[1][end++] = str[i++];
	return (cmd);
}

void	check_awk(char *str, char **env)
{
	char	**cmd;
	char	*path;

	path = NULL;
	cmd = awk_split(str);
	if (!cmd)
		free_exit_msg(ft_strjoin("pipex: command not found: ", str), \
			COM_N, NULL);
	if (str[0] == '/')
	{
		check_print_errors(cmd[0], cmd[0], 'p', cmd);
		execve(cmd[0], cmd, env);
	}
	else
	{
		path = get_path(env, cmd[0], NULL);
		path = join_path_to_cmd(path, cmd[0]);
		check_print_errors(path, cmd[0], 'c', cmd);
	}
	execve(path, cmd, env);
}
